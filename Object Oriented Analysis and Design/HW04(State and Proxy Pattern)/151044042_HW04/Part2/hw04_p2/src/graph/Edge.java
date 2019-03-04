package graph;

import java.io.Serializable;

/**
 * Class to represent an edge of a graph.
 * @param <T>
 */
public class Edge<T> implements Serializable {
    private Node<T> node1;
    private Node<T> node2;
    private int weight;

    /**
     * Constructs this edge with given nodes (weight = 1).
     * @param node1
     * @param node2
     */
    public Edge(Node<T> node1, Node<T> node2){
        this(node1, node2, 1);
    }

    /**
     * Construct this edge with given nodes and weight.
     * @param node1
     * @param node2
     * @param weight
     */
    public Edge(Node<T> node1, Node<T> node2, int weight){
        this.node1 = node1;
        this.node2 = node2;
        this.weight = weight;
        node1.addConnectionTo(node2, weight);
    }

    /**
     * Getter for node1.
     * @return node1
     */
    public Node<T> getNode1() {
        return node1;
    }

    /**
     * Getter for node2.
     * @return node2.
     */
    public Node<T> getNode2() {
        return node2;
    }

    /**
     * Getter for weight.
     * @return weight
     */
    public int getWeight() {
        return weight;
    }

    @Override
    public String toString() {
        return "[Edge]: " + node1 + " to " + node2 + " - " + weight;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;

        if (obj instanceof Edge){
            Edge other = (Edge) obj;
            return other.getNode1().equals(node1) && other.getNode2().equals(node2);
        }

        return false;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + node1.hashCode() * node2.hashCode();
        return result;
    }
}
