import methods.GaussianElimination;
import methods.MatrixInversion;

import javax.swing.*;
import javax.swing.text.DefaultCaret;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.util.ArrayList;

public class Application extends JFrame
{
    /**
     * Strategy pattern client. Manages which method to use.
     */
    private LinearEquationSolver linearEquationSolver;

    private String ENTER = "Enter";
    private JPanel contentPane;
    private String[] methodNames = {"Gaussian Elimination", "Matrix Inversion"};

    private JTextArea input;
    private JTextField output;
    private JButton enterButton;

    /**
     * Constructor for GUI.
     */
    public Application()
    {
        linearEquationSolver = new LinearEquationSolver();

        setTitle("Linear Equation Solver");
        setSize(600, 600);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        contentPane = new JPanel();
        contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
        contentPane.setOpaque(true);

        createInputAndOutputAreas();

        this.getContentPane().add(BorderLayout.CENTER, contentPane);
        this.pack();
    }

    /**
     * Creates input and output fields of GUI.
     */
    private void createInputAndOutputAreas()
    {
        createComboBox();
        ButtonListener buttonListener = new ButtonListener();
        input = new JTextArea(10, 20);
        input.setWrapStyleWord(true);

        JPanel outputPanel = new JPanel();
        outputPanel.setLayout(new FlowLayout());
        output = new JTextField(50);
        output.setEditable(false);
        enterButton = new JButton("Enter");
        enterButton.setActionCommand(ENTER);
        enterButton.addActionListener(buttonListener);
        DefaultCaret caret = (DefaultCaret) input.getCaret();
        caret.setUpdatePolicy(DefaultCaret.ALWAYS_UPDATE);
        contentPane.add(input);
        outputPanel.add(output);
        outputPanel.add(enterButton);
        contentPane.add(outputPanel);
    }

    /**
     * Creates method selection combobox.
     */
    private void createComboBox()
    {
        JComboBox comboBox = new JComboBox(methodNames);
        comboBox.addItemListener(e ->
        {
            if (e.getStateChange() == ItemEvent.SELECTED)
            {
                int index = comboBox.getSelectedIndex();
                if (index != -1)
                {
                    setTitle("Linear Equation Solver - " + methodNames[index]);
                    if (index == 0)
                        linearEquationSolver.setMethod(new GaussianElimination());
                    else if (index == 1)
                        linearEquationSolver.setMethod(new MatrixInversion());
                }
                else
                    setTitle("Linear Equation Solver");

            }
        });

        comboBox.setSelectedIndex(0);
        contentPane.add(comboBox);
    }

    public static void main(String[] args)
    {
        SwingUtilities.invokeLater(() ->
        {
            Application application = new Application();
            application.setVisible(true);
        });
    }

    /**
     * Custom class to manage click event.
     */
    public class ButtonListener implements ActionListener
    {

        /**
         * Parse the input, create a matrix and execute the selected method.
         * @param ev ActionEvent
         */
        public void actionPerformed(final ActionEvent ev)
        {
            if (!input.getText().trim().equals(""))
            {
                String cmd = ev.getActionCommand();
                if (ENTER.equals(cmd))
                {
                    String inp = input.getText();
                    ArrayList<String> lines = new ArrayList<>();
                    for (String line : inp.split("\n"))
                    {
                        lines.add(line.trim());
                    }
                    double[][] matrix = stringToDoubleArray(lines);
                    String result = linearEquationSolver.executeMethod(matrix);
                    output.setText(result);
                }
            }
        }

        /**
         * Converts the string lines into double array.
         * @param matrix A matrix as string
         * @return matrix as double array
         */
        private double[][] stringToDoubleArray(ArrayList<String> matrix)
        {
            // String i double array e çeviririz
            int n = matrix.size();
            double[][] arr = new double[n][n + 1];

            for (int i=0; i < n; i++)
            {
                String [] parts = matrix.get(i).split(",");
                for (int j = 0; j < n + 1; j++)
                    arr[i][j] = Double.parseDouble(parts[j]);
            }
            return arr;
        }
    }
}
