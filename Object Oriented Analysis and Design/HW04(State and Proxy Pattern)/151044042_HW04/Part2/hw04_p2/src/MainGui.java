import bulut.Service;
import graph.Edge;
import graph.Graph;
import graph.Node;
import methods.ServiceResult;

import javax.swing.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;
import java.util.List;

/**
 * A client implementation with GUI that uses the service that created (BulutServer).
 */
public class MainGui extends JFrame {
    private JTabbedPane tabbedPane1;
    private JPanel rootPanel;
    private JPanel loadBalancePanel;
    private JTextField ccInput;
    private JFormattedTextField tokensInput;
    private JButton loadBalanceBtn;
    private JPanel opetaionsPanel;
    private JTextArea inpGraph;
    private JPanel opSelTopPanel;
    private JTextPane resultPane;
    private JComboBox opSelection;
    private JButton solveBtn;
    private JTextField loadBalanceApiField;
    private JLabel currBalanceInfo;
    private JTextArea operationsApiKey;
    private JLabel loadBalanceResult;

    private String apiKey;
    private int balance;

    private Service service;
    private Graph graph;
    private boolean inputChanged = true;

    /**
     * Construct this client with user's apikey and balance.
     * @param apiKey
     * @param balance
     * @throws RemoteException
     * @throws NotBoundException
     */
    public MainGui(String apiKey, int balance) throws RemoteException, NotBoundException {
        Registry registry = LocateRegistry.getRegistry(1888);
        service = (Service) registry.lookup("RemoteGraphService001");

        this.apiKey = apiKey;
        this.balance = balance;

        add(rootPanel);

        setTitle("Bulut Cizge A.S.");
        setSize(650, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        initializeComponents();
        bindListeners();
    }

    /**
     * Creates graph from user input.
     * @return graph that generated from input.
     */
    private Graph createGraph() {
        String input = inpGraph.getText();
        String[] lines = input.split("\\r?\\n");
        if (lines.length < 2)
            return null;

        // add nodes to graph
        List<Node<Integer>> nodes = new ArrayList<>();
        int nodeNum = Integer.parseInt(lines[0]);
        for (int i = 0; i < nodeNum; i++)
            nodes.add(new Node<>(i));

        List<Edge<Integer>> edges = new ArrayList<>();

        for (int i = 1; i < lines.length; i++) {
            String[] nodesAndWeight = lines[i].split("\\s");
            int node1 = Integer.parseInt(nodesAndWeight[0]);
            int node2 = Integer.parseInt(nodesAndWeight[1]);
            int w = Integer.parseInt(nodesAndWeight[2]);

            if (node1 < 0 || node1 >= nodeNum || node2 < 0 || node2 >= nodeNum)
                return null;

            edges.add(new Edge(nodes.get(node1), nodes.get(node2), w));
        }

        return new Graph<>(nodes, edges);
    }

    /**
     * Binds components' listeners. One for graph input, one for load balance button and one for solve button.
     */
    private void bindListeners() {
        // if user types something, assume a new graph is given. use this information before solving a problem to decide
        // if we should create the graph again from user input.
        inpGraph.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                super.keyPressed(e);
                inputChanged = true;
            }
        });

        // gets apikey, credit card and amount from gui and performs the transaction via RMI service.
        loadBalanceBtn.addActionListener(e -> {
            String currApiKey = loadBalanceApiField.getText();
            String ccNo = ccInput.getText();
            String balanceStr = tokensInput.getText();
            int amount;
            try {
                amount = Integer.parseInt(balanceStr);
            } catch (NumberFormatException ex) {
                loadBalanceResult.setText("Please enter a number.");
                return;
            }

            try {
                ServiceResult result = service.loadCredit(currApiKey, ccNo, amount);
                loadBalanceResult.setText(result.getResultStr());
                apiKey = result.getApiKey();
                balance = result.getRemainingBalance();
                initializeComponents();
            } catch (RemoteException e1) {
                loadBalanceResult.setText("There was a connection error.");
            }
        });

        // creates graph object from user input and apply the selected method on this graph.
        solveBtn.addActionListener(e -> {
            if (inputChanged) {
                graph = createGraph();
                inputChanged = false;
            }

            if (graph == null || graph.getNodes().isEmpty()) {
                resultPane.setText("Input graph is not setup correctly.");
                return;
            }

            String currApiKey = operationsApiKey.getText();
            StringBuilder sb = new StringBuilder();
            ServiceResult result;
            try {
                int selIdx = opSelection.getSelectedIndex();
                long t = System.currentTimeMillis();
                if (selIdx == 0)
                    result = service.minimumSpanningTree(currApiKey, graph);
                else
                    result = service.incidenceMatrix(currApiKey, graph);

                sb.append("Total elapsed time (including reaching server) is ")
                        .append(System.currentTimeMillis() - t).append("ms.\n");

                if (result.getError() == null || result.getError().isEmpty()) {
                    sb.append("Result:\n").append(result.getResultStr()).append('\n');
                }
                else {
                    sb.append("It seems there was an error:\n").append(result.getError()).append('\n');
                }

                apiKey = result.getApiKey();
                balance = result.getRemainingBalance();
                initializeComponents();

                resultPane.setText(sb.toString());
            } catch (RemoteException re) {
                resultPane.setText("There was a connection error.");
            }

        });
    }

    /**
     * Sets values for text fields of GUI.
     */
    private void initializeComponents() {
        currBalanceInfo.setText("Your current balance is " +
                (balance > 0 ? (balance + ".") : (balance + ". Load balance!")));

        operationsApiKey.setText(apiKey);
        loadBalanceApiField.setText(apiKey);
    }

}
