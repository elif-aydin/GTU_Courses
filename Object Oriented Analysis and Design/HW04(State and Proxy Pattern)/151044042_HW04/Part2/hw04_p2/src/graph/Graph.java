package graph;

import java.io.Serializable;
import java.util.List;
import java.util.Set;

/**
 * Class to represent a graph structure.
 * @param <T>
 */
public class Graph<T> implements Serializable {

    private List<Edge<T>> edges;
    private List<Node<T>> nodes;

    /**
     * Constructs this graph with given nodes.
     * @param nodes
     */
    public Graph(List<Node<T>> nodes) {
        this.nodes = nodes;
    }

    /**
     * Constructs this graph with given nodes and edges.
     * @param nodes
     */
    public Graph(List<Node<T>> nodes, List<Edge<T>> edges){
        this.edges = edges;
        this.nodes = nodes;
    }

    /**
     * Getter for edges.
     * @return edges
     */
    public List<Edge<T>> getEdges() {
        return edges;
    }

    /**
     * Getter for nodes.
     * @return nodes
     */
    public List<Node<T>> getNodes() {
        return nodes;
    }

    /**
     * Setter for edges.
     * @param edges edge list
     */
    public void setEdges(List<Edge<T>> edges) {
        this.edges = edges;
    }

    /**
     * Setter for nodes.
     * @param nodes node list
     */
    public void setNodes(List<Node<T>> nodes) {
        this.nodes = nodes;
    }

    /**
     * Gets a string representation of this graph
     * @return graph as string
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Graph:\n");
        for (Edge edge : edges){
            sb.append(edge).append("\n");
        }
        return sb.toString();
    }
}
