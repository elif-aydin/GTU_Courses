import java.util.EmptyStackException;

/**
 * Created by elif on 21-Mar-17.
 */
public class StackC<E> implements StackInterface<E>
{
    private Node<E> head = null;
    private int size = 0;

    /**
     * This method pushes an item onto the top of the stack and returns
     * the item pushed.
     * @param obj The object to be inserted
     * @return The object inserted
     */
    @Override
    public E push(E obj)
    {
        Node<E> newTop = new Node(obj,head);
        head = newTop;
        size ++;
        return obj;
    }

    /**
     * This method Returns the object at the top of the stack
     * and removes it.
     * @return The object at the top of the stack
     * @throws EmptyStackException if stack is empty
     */
    @Override
    public E pop()
    {
        if(isEmpty())
            throw new EmptyStackException();

        Node<E> oldTop = head;
        head = head.next;
        size --;
        return oldTop.data;}

    /**
     * This method returns true if the stack is empty; otherwise,
     * returns false.
     * @return true (false) if the stack is empty (not empty)
     */
    @Override
    public boolean isEmpty()
    {
        return size() == 0 ;
    }

    /**
     * This method returns the stack size
     * @return The stack size
     */
    @Override
    public int size()
    {
        return size;
    }

    /**
     * Returns a string representation of this collection
     * @return a string representation of this collection
     */
    @Override
    public String toString()
    {
        String temp = "";

        Node tempNode = head;
        for (int i = 0; i < this.size() ; i++)
        {
            temp += (tempNode.data.toString() + ",");
            tempNode = tempNode.next;
        }
        return temp.substring(0, temp.length()-1);
    }

    /**
     * A Node is the building block for a single linked list.
     */
    class Node<E>
    {
        private E data;
        private Node<E> next;

        // Constructors
        /** Creates a new node with a null next field.
         @param data The data stored
         */
        Node(E data)
        {
            this(data, null);
        }

        /** Creates a new node that references another node.
         @param data The data stored
         @param next The node referenced by new node
         */
        private Node(E data, Node<E> next)
        {
            this.data = data;
            this.next = next;
        }

        public E getData()
        {
            return data;
        }

        public void setData(E data)
        {
            this.data = data;
        }

        public Node<E> getNext()
        {
            return next;
        }

        public void setNext(Node<E> next)
        {
            this.next = next;
        }
    }

}
