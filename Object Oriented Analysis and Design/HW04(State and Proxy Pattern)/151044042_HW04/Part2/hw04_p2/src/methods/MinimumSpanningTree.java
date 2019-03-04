package methods;

import graph.Graph;
import graph.Node;

import java.util.Map;
import java.util.Set;

/**
 * Minimum Spanning Tree implementation that implements Algorithm interface.
 * @param <T>
 */
public class MinimumSpanningTree<T> implements Algorithm {
    private Graph graph;
    private int[] parentArr;

    /**
     * Constructs this method with given graph.
     * @param graph graph
     */
    public MinimumSpanningTree(Graph<T> graph) {
        this.graph = graph;
        this.parentArr = new int[graph.getNodes().size()];
    }

    /**
     * Runs this method's algorithm.
     */
    @Override
    public void execute() {
        int[] keyArr = new int[graph.getNodes().size()];
        boolean[] marked = new boolean[graph.getNodes().size()];

        for (int i = 0; i < parentArr.length; i++) {
            marked[i] = false;
            keyArr[i] = Integer.MAX_VALUE;
        }

        keyArr[0] = 0;
        parentArr[0] = -1;

        for (int i = 0; i < graph.getNodes().size() - 1; i++) {
            int connect = nextMin(keyArr, marked);

            Node connectingNode = (Node) graph.getNodes().get(connect);
            Set<Map.Entry<Node<T>, Integer>> adjs = connectingNode.getAdjacents().entrySet();
            for (Map.Entry<Node<T>, Integer> adj : adjs) {
                int n = graph.getNodes().indexOf(adj.getKey());
                int w = adj.getValue();

                if (!marked[n] && w < keyArr[n]) {
                    parentArr[n] = connect;
                    keyArr[n] = w;
                }
            }
        }

    }

    /**
     * Extracts the result from the data that generated from execute() method.
     * @return	method's result as Result object
     */
    @Override
    public Result getResult() {
        StringBuilder sb = new StringBuilder("Follow the nodes:\n").append("From To\n");
        for (int i = 1; i < parentArr.length; i++) {
            sb.append(parentArr[i]).append(" - ").append(i).append('\n');
        }
        sb.append('\n');

        return new Result(sb.toString(), null);
    }


    /**
     * Gets next min node index to process.
     * @param keyArr
     * @param marked
     * @return
     */
    private int nextMin(int[] keyArr, boolean[] marked)
    {
        int min = Integer.MAX_VALUE;
        int min_index = -1;

        for (int i = 0; i < keyArr.length; i++)
            if (!marked[i] && keyArr[i] < min) {
                min = keyArr[i];
                min_index = i;
            }

        marked[min_index] = true;
        return min_index;
    }
}
