package bulut;

import graph.Graph;
import methods.ServiceResult;

import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 * An interface for Java RMI to support graph operations as well as loading balance for the user.
 */
public interface Service extends Remote {


    /**
     * Loads balance for the user.
     * @param apiKey identifier for the user
     * @param creditCard card no
     * @param numOfCredits balane to load
     * @return  success or failure as wrapped
     * @throws RemoteException from RMI
     */
    ServiceResult loadCredit(String apiKey, String creditCard, int numOfCredits) throws RemoteException;

    /**
     * Calculates the minimum spanning tree of given graph. Assumes there is a minimum spanning tree in graph.
     * @param apiKey identifier for the user
     * @param graph graph to work on
     * @return mst as string wrapped in Result
     * @throws RemoteException from RMI
     */
    ServiceResult minimumSpanningTree(String apiKey, Graph graph) throws RemoteException;

    /**
     * Calculates the incidence matrix of given graph.
     * @param apiKey identifier for the user
     * @param graph graph to work on
     * @return incidence matrix as string wrapped in Resul
     * @throws RemoteException from RMI
     */
    ServiceResult incidenceMatrix(String apiKey, Graph graph) throws RemoteException;
}
