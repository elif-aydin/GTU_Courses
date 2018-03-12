import java.util.NoSuchElementException;


/**
 * Created by elif on 17-Apr-17.
 */
public class BinaryHeap<E extends Comparable> extends BinaryTree<E> implements MyQueue<E>
{

    private int size = 0;

    /**
     * This method adds new items to correct place in heap.
     * @param item Item to be ad
     * @return Always true
     */
    private boolean add (E item)
    {
        ++size;
        if(this.root == null)
        {
            root = new Node<E>(item);
            return true;
        }

        else
        {
            Node <E> node = addToEnd(this.root, item);
            while(node != null && node.parent != null && node.data.compareTo(node.parent.data)< 0)
            {
                E temp = node.data;
                node.data = node.parent.data;
                node.parent.data= temp;
                node = node.parent;
            }
            return true;
        }
    }

    /**
     * This method adds new items to heap.
     * @param node Node to find a correct place
     * @param item Item to be add
     * @return Parent node of adding node
     */
    private Node<E> addToEnd(Node<E> node, E item)
    {
        if(node.left == null)
        {
            node.left = new Node<E>(node, item);
            return node.left;
        }
        else if(node.right == null)
        {
            node.right = new Node<E>(node, item);
            return node.right;
        }

        else if (hasEmptyChild(node.left))
            return addToEnd(node.left, item);

        else if (hasEmptyChild(node.right))
            return addToEnd(node.right, item);

        else if(findMaxDepth(node.left) == findMaxDepth(node.right))
            return addToEnd(node.left, item);

        else
            return addToEnd(node.right, item);
    }

    /**
     * This method check if there is any available place
     * @param node to be add
     * @return true or false
     */
    private boolean hasEmptyChild(Node<E> node)
    {
        if (node == null)
            return false;
        return size(node.left) != size(node.right);
    }

    /**
     * This method check children status for given node
     * @param node node to be check
     * @return true or false
     */
    private boolean has2Children(Node<E> node)
    {
        return (node.left != null && node.right != null);
    }

    /**
     * This method check children status for given node
     * @param node node to be check
     * @return true or false
     */
    private boolean hasNoChildren(Node <E> node)
    {
        return (node.left == null && node.right == null);
    }

    /**
     * This method deletes the root in given tree
     * @param toDelete node to be delete
     * @param from start node for search
     * @return true or false
     */
    private boolean deleteNode(Node<E> toDelete, Node<E> from)
    {
        if (from == null || hasNoChildren(from))
            return false;

        if (from.left.equals(toDelete))
        {
            from.left = null;
            return true;
        }
        else if (from.right != null && from.right.equals(toDelete))
        {
            from.right = null;
            return true;
        }
        else
        {
            boolean res = deleteNode(toDelete, from.left);
            return res || deleteNode(toDelete, from.right);
        }
    }

    /**
     * This method finds the last node in given tree
     * @param node tree to be search
     * @return true or false
     */
    private Node<E> findLastNode(Node <E> node)
    {
        if (hasNoChildren(node))
            return node;

        else
        {
            if (findMaxDepth(node.right) >= findMaxDepth(node.left))
                return findLastNode(node.right);

            else
                return findLastNode(node.left);
        }
    }

    /**
     * This method find max depth in given tree
     * @param node tree to be search
     * @return true or false
     */
    private int findMaxDepth(Node<E> node)
    {
        if (node == null)
            return 0;

        else
        {
            /* Computes the depth of each subtree */
            int leftDepth = findMaxDepth(node.left);
            int rightDepth = findMaxDepth(node.right);

            /* Use the larger */
            if (leftDepth > rightDepth)
                return (leftDepth + 1);
            else
                return (rightDepth + 1);
        }
    }

    /**
     * Retrieves, but does not remove, the head of this queue, or returns null if this queue is empty
     * @return the head of this queue, or null if this queue is empty
     * @throws NoSuchElementException if the queue is empty
     */
    @Override
    public E peek() throws NoSuchElementException
    {
        if (size == 0)
            return null;
        return root.data;
    }

    public int size()
    {
        return size;
    }

    private int size(Node<E> node)
    {
        if(node == null)
            return 0;

        return (1 + size(node.left) + size(node.right));
    }

    /**
     * Inserts the specified element into this queue
     * @param data the element to add
     * @return true if the element was added to this queue, else false
     */
    @Override
    public boolean offer(E data)
    {
        return add(data);
    }

    /**
     * Retrieves and removes the head of this queue, or returns null if this queue is empty
     * @return the head of this queue, or null if this queue is empty
     * @throws NoSuchElementException if the queue is empty
     */
    @Override
    public E poll() throws NoSuchElementException
    {
        if (size == 0)
            return null;

        E returnVal = root.data;
        if (size == 1) {
            root = null;
            --size;
            return returnVal;
        }

        Node<E> node = findLastNode(root);
        deleteNode(node, root);
        root.data = node.data;

        Node<E> temp = root;
        Node<E> min;
        while (temp != null && !hasNoChildren(temp) && (min = getMinChild(temp)).data.compareTo(temp.data) < 0)
        {
            E t = min.data;
            min.data = temp.data;
            temp.data = t;
            temp = min;
        }

        --size;
        return returnVal;
    }

    /**
     * This method return minimum data in given tree
     * @param node tree to be search
     * @return minimum fata
     */
    private Node<E> getMinChild(Node<E> node)
    {
        if (hasNoChildren(node))
            return null;

        if (has2Children(node))
        {
            if (node.left.data.compareTo(node.right.data) > 0)
                return node.right;
            return node.left;
        }
        else
            return node.left;
    }
}