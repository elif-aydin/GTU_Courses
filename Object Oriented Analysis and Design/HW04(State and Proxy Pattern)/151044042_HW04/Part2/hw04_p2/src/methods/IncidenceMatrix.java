package methods;

import graph.Edge;
import graph.Graph;

/**
 * Incidence matrix implementation that implements Algorithm interface.
 * @param <T>
 */
public class IncidenceMatrix<T> implements Algorithm {
    private Graph graph;
    private int[][] matrix;

    /**
     * Constructs this method with given graph.
     * @param graph graph
     */
    public IncidenceMatrix(Graph graph) {
        this.graph = graph;
        matrix = new int[graph.getNodes().size()][graph.getEdges().size()];
        for (int i = 0; i < graph.getNodes().size(); i++) {
            for (int j = 0; j < graph.getEdges().size(); j++) {
                matrix[i][j] = 0;
            }
        }
    }

    /**
     * Runs this method's algorithm.
     */
    @Override
    public void execute() {
        int edgeIdx = 0;
        for (Object e : graph.getEdges()) {
            Edge edge = (Edge) e;
            int n1 = graph.getNodes().indexOf(edge.getNode1());
            int n2 = graph.getNodes().indexOf(edge.getNode2());
            // according to Incidence matrix - Wikipedia
            //https://en.wikipedia.org/wiki/Incidence_matrix
            matrix[n1][edgeIdx] = -1;   // if the edge is leaving the node, -1
            matrix[n2][edgeIdx] = 1;    // if the edge is entering the node, 1
            edgeIdx++;
        }
        System.out.println("incidence done.");
    }

    /**
     * Extracts the result from the data that generated from execute() method.
     * @return	method's result as Result object
     */
    @Override
    public Result getResult() {
        StringBuilder sb = new StringBuilder();
        for (int[] matrix1 : matrix) {
            for (int j = 0; j < matrix1.length; j++) {
                sb.append(matrix1[j]).append('\t');
            }
            sb.append('\n');
        }
        sb.append('\n');
        return new Result(sb.toString(), null);
    }
}
