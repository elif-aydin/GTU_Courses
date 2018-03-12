import java.util.*;

/**
 * Created by elif on 03-Apr-17.
 */

public class MyBinaryTree <E> extends BinaryTree<E> implements Iterable<E>
{
    public void add(E data)
    {
        if (root == null)
            root = new Node<E>(data);
        else
            this.add(data, root);
    }

    /**
     * This method adds the specified element to this tree.
     * @param data Adds the specified element to this tree.
     * @param node Adding place
     */
    private void add(E data, Node node)
    {
        Random random = new Random();
        int t = random.nextInt();
        if (t % 2 == 0)
        {
            if (node.left == null)
                node.left = new Node(data);
            else
                add(data, node.left);
        }

        else
        {
            if (node.right == null)
                node.right = new Node(data);
            else
                add(data, node.right);
        }

    }

    /**
     * Returns an iterator over elements of type.
     * @return an Iterator.
     */
    @Override
    public Iterator<E> iterator()
    {
        MyIterator iter = new MyIterator(root);
        return iter;
    }

    /**
     * Iterator class implementation
     * @param <E>
     */
    public class MyIterator<E> implements Iterator<E>
    {
        Stack<Node> myStack = new Stack<>();

        /**
         * Constructor
         */
        public MyIterator(Node root) throws EmptyStackException
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
                throw new NoSuchElementException(/*"All nodes have been visited!"*/);

            Node res = myStack.pop();

            if (res.right != null)
                myStack.push(res.right);

            if (res.left != null)
                myStack.push(res.left);

            return (E) res.data;
        }
    }

}