package bulut;

import graph.Graph;
import methods.IncidenceMatrix;
import methods.MinimumSpanningTree;
import methods.ServiceResult;

import java.rmi.AlreadyBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

/**
 * A server implementation for Bulut A.S.
 */
public class BulutServer extends UnicastRemoteObject implements Service {

    private final Integer MST_PRICE = 10;
    private final Integer IN_PRICE = 20;

    private Map<String, Integer> apiBalanceMap;

    /**
     * Construct server.
     * @param apiKey
     * @param balance
     * @throws RemoteException
     * @throws AlreadyBoundException
     */
    public BulutServer(String apiKey, int balance) throws RemoteException, AlreadyBoundException {
        System.err.println(">> Server is being created.");
        apiBalanceMap = new HashMap<>();
        apiBalanceMap.put(apiKey, balance);

        // get registry and bind this object so that it can be found through RMI.
        Registry registry = LocateRegistry.getRegistry(1888);
        registry.bind("RemoteGraphService001", this);
    }

    private void printStartingInfo(String methodName, String apikey) {
        System.err.println("[Server - " + new Date() + "] " + methodName + " called from client " + apikey + ".");
    }

    private void printEndingInfo(String methodName, String apikey, long elapsedTime) {
        System.err.println("[Server - " + new Date() + "] " + methodName + " method completed for " + apikey + " in " + elapsedTime + "ms.");
    }

    /**
     * Loads balance for the user.
     * @param apiKey identifier for the user
     * @param creditCard card no
     * @param numOfCredits balane to load
     * @return  success or failure as wrapped
     * @throws RemoteException from RMI
     */
    @Override
    public synchronized ServiceResult loadCredit(String apiKey, String creditCard, int numOfCredits) throws RemoteException {
        printStartingInfo("loadCredit", apiKey);

        long start = System.currentTimeMillis();
        Integer current = apiBalanceMap.get(apiKey);
        if (current == null)
            current = 0;

        apiBalanceMap.put(apiKey, current + numOfCredits);
        printEndingInfo("loadCredit", apiKey, System.currentTimeMillis() - start);
        return new ServiceResult("Balance successfully loaded.", null, apiKey, current + numOfCredits);
    }

    /**
     * Calculates the minimum spanning tree of given graph. Assumes there is a minimum spanning tree in graph.
     * @param apiKey identifier for the user
     * @param graph graph to work on
     * @return mst as string wrapped in Result
     * @throws RemoteException from RMI
     */
    @Override
    public synchronized ServiceResult minimumSpanningTree(String apiKey, Graph graph) throws RemoteException {
        printStartingInfo("minimumSpanningTree", apiKey);

        long start = System.currentTimeMillis();
        Integer temp = apiBalanceMap.get(apiKey);
        if (temp == null)
            return new ServiceResult(null, "We don't know this API key! You should load balance first if you want to use this API key.", apiKey, 0);
        if (temp < MST_PRICE)
            return new ServiceResult(null, "You don't have enough balance.", apiKey, temp);

        MinimumSpanningTree mst = new MinimumSpanningTree(graph);
        mst.execute();

        apiBalanceMap.put(apiKey, temp - MST_PRICE);
        printEndingInfo("minimumSpanningTree", apiKey, System.currentTimeMillis() - start);
        return new ServiceResult(mst.getResult(), apiKey, temp - MST_PRICE);
    }

    /**
     * Calculates the incidence matrix of given graph.
     * @param apiKey identifier for the user
     * @param graph graph to work on
     * @return incidence matrix as string wrapped in Resul
     * @throws RemoteException from RMI
     */
    @Override
    public synchronized ServiceResult incidenceMatrix(String apiKey, Graph graph) throws RemoteException {
        printStartingInfo("incidenceMatrix", apiKey);

        long start = System.currentTimeMillis();
        Integer temp = apiBalanceMap.get(apiKey);
        if (temp == null)
            return new ServiceResult(null, "We don't know this API key! You should load balance first if you want to use this API key.", apiKey, 0);
        if (temp < IN_PRICE)
            return new ServiceResult(null, "You don't have enough balance.", apiKey, temp);

        IncidenceMatrix im = new IncidenceMatrix(graph);
        im.execute();

        apiBalanceMap.put(apiKey, temp - IN_PRICE);
        printEndingInfo("incidenceMatrix", apiKey, System.currentTimeMillis() - start);
        return new ServiceResult(im.getResult(), apiKey, temp - IN_PRICE);
    }
}
