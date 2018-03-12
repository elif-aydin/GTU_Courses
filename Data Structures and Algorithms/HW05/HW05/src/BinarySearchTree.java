import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;
import java.util.NoSuchElementException;
import java.util.EmptyStackException;

/** A class to represent a binary search tree.
 *  @author Koffman and Wolfgang
 */

public class BinarySearchTree <E extends Comparable <E>> extends BinaryTree <E>
{

    /**
     * @param item The object being inserted
     * @return true if the object is inserted, false if the object already exists in the tree
     */
    public void add(E item)
    {
        root = add(root, item);
    }

    /**
     * @param tempRoot The local root of the subtree
     * @param item The object to be inserted
     * @return The new local root that now contains the inserted item
     */
    private Node < E > add(Node < E > tempRoot, E item)
    {
        if (tempRoot == null)
            return new Node <E> (item);

        else if (item.compareTo(tempRoot.data) == 0) // item is equal to localRoot.data
            return tempRoot;

        else if (item.compareTo(tempRoot.data) < 0) // kucukse sol
        {
            tempRoot.left = add(tempRoot.left, item);
            return tempRoot;
        }
        else // buyukse sag
        {
            tempRoot.right = add(tempRoot.right, item);
            return tempRoot;
        }
    }

    /**
     * Returns an iterator over elements of type.
     * @return an Iterator.
     */
    public Iterator<E> iterator()
    {
        MyLevelOrderIterator iter = new MyLevelOrderIterator(root);
        return iter;
    }

    public Iterator<E> preOrderIterator()
    {
        MyPreOrderIterator iter = new MyPreOrderIterator(root);
        return iter;
    }

    public class MyPreOrderIterator<E> implements Iterator<E>
    {
        Stack<Node> myStack = new Stack<Node>();

        /**
         * Constructor
         */
        public MyPreOrderIterator(Node root) throws EmptyStackException
        {
            if (root != null)
                myStack.push(root); // Sdd to end of queue
            else
                throw new EmptyStackException();
        }

        /**
         * Returns true if the iteration has more elements.
         * In other words, returns code true if would
         * return an element rather than throwing an exception.
         *
         * @return true if the iteration has more elements
         */
        @Override
        public boolean hasNext()
        {
            return !(myStack.isEmpty());
        }

        /**
         * Returns the next element in the iteration.
         *
         * @return the next element in the iteration
         * @throws NoSuchElementException if the iteration has no more elements
         */
        @Override
        public E next() throws NoSuchElementException
        {
            if (!hasNext())
                throw new NoSuchElementException();

            Node res = myStack.pop();

            if (res.right != null)
                myStack.push(res.right);

            if (res.left != null)
                myStack.push(res.left);

            return (E) res.data;
        }
    }

    public class MyLevelOrderIterator<E> implements Iterator<E>
    {
        Queue<Node> myQueue = new LinkedList<Node>();

        /**
         * Constructor
         */
        public MyLevelOrderIterator(Node root) throws NoSuchElementException
        {
            if (root != null)
                myQueue.offer(root); // Sdd to end of queue
            else
                throw new NoSuchElementException();
        }

        /**
         * Returns true if the iteration has more elements.
         * In other words, returns code true if would
         * return an element rather than throwing an exception.
         *
         * @return true if the iteration has more elements
         */
        @Override
        public boolean hasNext()
        {
            return !(myQueue.isEmpty());
        }

        /**
         * Returns the next element in the iteration.
         *
         * @return the next element in the iteration
         * @throws NoSuchElementException if the iteration has no more elements
         */
        @Override
        public E next() throws NoSuchElementException
        {
            if (!hasNext())
                throw new NoSuchElementException();

            if(!(myQueue.isEmpty()))
            {
                Node res = myQueue.poll();

                if (res.left != null)
                    myQueue.offer(res.left);

                if (res.right != null)
                    myQueue.offer(res.right);

                return (E) res.data;
            }
            else
                return null;
        }
    }
}


