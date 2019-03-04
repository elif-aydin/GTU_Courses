package graph;

import java.io.Serializable;
import java.util.*;

/**
 * Class to represent a node in a graph.
 * @param <T>
 */
public class Node<T> implements Serializable {
    private T data;

    private Map<Node<T>, Integer> to;
    private Map<Node<T>, Integer> from;

    /**
     * Constructs this node with given data.
     * @param t
     */
    public Node(T t){
        data = t;
        to = new HashMap<>();
        from = new HashMap<>();
    }

    /**
     * Adds a connection from this node to given node
     * @param node given node
     * @param weight weight
     */
    public void addConnectionTo(Node<T> node, int weight){
        if (to.containsKey(node))
            to.put(node, weight + to.get(node));
        else
            to.put(node, weight);
    }


    /**
     * Gets adjacents of this node.
     * @return
     */
    public Map<Node<T>, Integer> getAdjacents() { return to; }

    @Override
    public String toString() {
        return "[Node: " + data.toString() + "]";
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;

        if (obj != null){
            return obj == data;
        }

        return false;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((data == null) ? 0 : data.hashCode());
        return result;
    }
}
