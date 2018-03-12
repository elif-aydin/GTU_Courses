import java.util.Iterator;
import java.util.NoSuchElementException;

/** Class to represent a linked list with a link from each node to the
 * next node. SingleLinkedList does not implement the List interface.
 */
public class SingleLinkedList<T>
{
    private Node<T> head = null;
    private Node<T> removeList = null;

    private int size = 0;
    private int removeListSize = 0;


    /** Get the data at index
     *@param index The position of the data to return
     *@return The data at index
     *@throws IndexOutOfBoundsException if index is out of range
     */
    public T get(int index)
    {
        if (index < 0 || index >= size)
            throw new IndexOutOfBoundsException("" + index);

        return getNode(index).getData();
    }


    /** Store a reference to anEntry in the element at position index.
     *@param index The position of the item to change
     *@param data The new data
     *@return The data previously at index
     *@throws IndexOutOfBoundsException if index is out of range
     */
    public T set(int index, T data)
    {
        if (index < 0 || index >= size)
            throw new IndexOutOfBoundsException("" + index);

        Node<T> node = getNode(index);
        T result = node.getData();
        node.setData(data);
        return result;
    }


    /** Insert the specified item at index
     *@param index The position where item is to be inserted
     *@param data The item to be inserted
     *@throws IndexOutOfBoundsException if index is out of range
     */
    public void add(int index, T data)
    {
        if (index < 0 || index > size)
            throw new IndexOutOfBoundsException("" + index);

        if (index == 0)
            addFirst(data);
        else
        {
            Node<T> node = getNode(index - 1); // addAfter'ı çağıracağımız için bi öncesini buluyoruz
            addAfter(node, data);
        }
    }


    /** Append item to the end of the list
     *@param data The item to be appended
     *@return true (as specified by the Collection interface)
     */
    public boolean add(T data)
    {
        add(size, data);
        return true;
    }


    /**
     * Remove the node from the given index in the list
     * @param index The item to be removed
     * @return The removed data
     */
    public T remove(int index)
    {
        if (index < 0 || index >= size){
            throw new IndexOutOfBoundsException("" + index);
        }

        if (index == 0)
            return removeFirst();

        Node<T> node = getNode(index - 1);
        return removeAfter(node);
    }


    /** Add an item to the front of the list.
     *@param item The item to be added
     */
    private void addFirst(T item)
    {
        if (head == null)
            head = new Node<T>(item);
        else
        {
            Node<T> temp = head;
            head = getFromRemovedList();

            if (head == null)
                head = new Node<T>(item);
            else
                head.setData(item);
                head.setNext(temp);
        }
        size++;
    }


    /** Add a node after a given node
     *@param node The node preceding the new item
     *@param item The item to insert
     */
    private void addAfter(Node<T> node, T item)
    {
        Node newNode = getFromRemovedList();
        if (newNode == null)
            newNode = new Node<T>(item);
        else
            newNode.setData(item);

        Node<T> before = node.getNext();
        newNode.setNext(before);
        node.setNext(newNode);
        size++;
    }


    /** Remove the first node from the list
     *@return The removed node's data or null if the list is empty
     */
    private T removeFirst()
    {
        if (head == null)
            return null;

        T data = head.getData();
        addToRemoveList(removeList, head);
        head = head.getNext();
        size--;

        return data;
    }


    /** Remove the node after a given node
     *@param node The node before the one to be removed
     *@return The data from the removed node, or null
     *if there is no node to remove
     */
    private T removeAfter(Node<T> node)
    {
        Node<T> after = node.getNext();
        if (after != null)
        {
            node.setNext(after.getNext());
            size--;
            addToRemoveList(removeList, after);
            return after.getData();
        }
        else
            return null;
    }


    /**
     * Adds the deleted nodes to another list
     * @param to Place to add
     * @param node Node to be added
     */
    private void addToRemoveList(Node<T> to, Node<T> node)
    {
        if (removeList == null)
        {
            node.setNext(null);
            removeList = node;
            removeListSize++;
        }

        else if (to.getNext() == null)
        {
            node.setNext(null);
            to.setNext(node);
            ++removeListSize;
        }

        else addToRemoveList(to.getNext(), node);
    }

    /**
     * If there is a deleted nodes, give this node.
     * @return Node to be used
     */
    private Node<T> getFromRemovedList()
    {
        if (removeList == null)
            return null;

        Node<T> node = removeList;
        removeList = removeList.getNext();
        --removeListSize;
        return node;
    }


    /** Find the node at a specified position
     *@param index The position of the node sought
     *@return The node at index or null if it does not exist
     */
    private Node<T> getNode(int index)
    {
        Node n = head;
        for (int i = 0; i < index && n != null; i++)
            n = n.getNext();

        return n;
    }


    /**
     * Creates a creates a String of deleted nodes
     * @return Creates a String of deleted nodes
     */
    public String deletedToString()
    {
        String toBeReturned = "[";
        Node<T> node = removeList;
        while(node != null)
        {
            toBeReturned += node.data.toString();
            if (node.next != null)
                toBeReturned += " ";
            node = node.next;
        }
        return toBeReturned + "]\n";
    }

    /**
     * Implements to string method
     * @return Created string
     */
    @Override
    public String toString()
    {
        String sb = "";
        Node<T> node = head;
        while (node != null)
        {
            sb += (node.getData() + "\n");
            node = node.getNext();
        }
        return sb;
    }


    /**
     * Generates string recursively
     * @return String of instance
     */
    public String recursiveToString()
    {
        return recursiveToString(head);
    }


    /**
     * Generates string recursively
     * @param node Node to start for toString
     * @return String of instance
     */
    private String recursiveToString(Node<T> node)
    {
        if (node == null)
            return "";

        String res = node.getData().toString();
        if (node.getNext() != null)
            res += " -> ";

        return res + recursiveToString(node.getNext());
    }


    /**
     * Generates reverse string recursively
     * @return Reverse string of instance
     */
    public String reverseToString()
    {
        return reverseToString(head);
    }


    /**
     * Generates reverse string recursively
     * @param node Node to start for toString
     * @return Reverse string of instance
     */
    private String reverseToString(Node<T> node)
    {
        if (node == null)
            return "";

        String res = node.getData().toString();
        if (node.getNext() != null)
            res = " -> " + res;

        return reverseToString(node.getNext()) + res;
    }


    public Iterator iterator()
    {
        return new MyIterator(head);
    }

    /** An iterator for reversing Nodes*/
    class MyIterator implements Iterator
    {
        private Node<T> nextItem = null;
        private Node<T> lastReturned = null;

        MyIterator(Node<T> node)
        {
            nextItem = node;
        }

        @Override
        public boolean hasNext()
        {
            return nextItem != null;
        }

        @Override
        public Object next()
        {
            if (!hasNext())
                throw new NoSuchElementException();
            lastReturned = nextItem;
            nextItem = nextItem.getNext();
            return lastReturned.getData();
        }
    }

    public int size()
    {
        return size;
    }

    /**
     * A Node is the building block for a single linked list.
     */
    class Node<T>
    {
        private T data;
        private Node<T> next;

        // Constructors
        /** Creates a new node with a null next field.
         @param data The data stored
         */
        Node(T data)
        {
            this(data, null);
        }

        /** Creates a new node that references another node.
         @param data The data stored
         @param next The node referenced by new node
         */
        private Node(T data, Node<T> next)
        {
            this.data = data;
            this.next = next;
        }

        public T getData()
        {
            return data;
        }

        public void setData(T data)
        {
            this.data = data;
        }

        public Node<T> getNext()
        {
            return next;
        }

        public void setNext(Node<T> next)
        {
            this.next = next;
        }
    }

}
