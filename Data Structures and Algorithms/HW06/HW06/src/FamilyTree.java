import java.util.*;

public class FamilyTree extends BinaryTree {

    /**
     * One parameter constructor to build a person’s family
     * @param name Person's name
     */
    public FamilyTree(String name)
    {
        root = new Node(new Person(name, null));
    }

    /**
     *
     * This method add person to the family tree
     * @param name Person's name
     * @param parentName Person's parent name
     * @param parentNickName Person's nickname
     * @return true or false
     */
    public boolean add(String name, String parentName, String parentNickName)
    {
        Node t = findANode(parentName, root);
        if (t == null) {
            throw new NoSuchElementException("You don't have a person with this name in the family tree: " + parentName);
        }
        String ss = parentNickName.replace("ebu-", "").replace("ibn-", "");
        t = findANode(ss, root);
        if (t == null) {
            if (!name.equals(ss) || parentNickName.split("-")[0].equals("ibn"))
                throw new NoSuchElementException("You don't have a person with this name in the family tree: " + ss);
        }

        List<Node> possibleNodes = new ArrayList<Node>();

        findByName(parentName, root, possibleNodes);
        Node toAdd;

        if (possibleNodes.size() == 0)
            return false;
        else if (possibleNodes.size() == 1)
            toAdd = possibleNodes.get(0);

        else
        {
            List<Node> finalPossibles = getFinalPossibleNodes(parentNickName, possibleNodes);
            if (finalPossibles.size() > 1)
                throw new IllegalStateException("There are more than one place that could be added.");

            toAdd = finalPossibles.get(0);
        }

        if (toAdd != null)
            addChild(toAdd, name);

        return true;
    }

    /**
     * This method finds the nodes that matches with the parent's nick name.
     * @param parentNick parent's nick name
     * @param possibleNodes the nodes have the same name
     * @return matched nodes
     */
    private List<Node> getFinalPossibleNodes(String parentNick, List<Node> possibleNodes)
    {
        String[] tokens = parentNick.split("-");
        String pre = tokens[0];
        String post = tokens[1];
        List<Node> possibles = new ArrayList<Node>();

        if (pre.equals("ibn"))
        {
            for (Node n : possibleNodes)
            {
                Person current = (Person) n.data;
                if (current.parent != null)
                    if (current.parent.name.equals(post))
                        possibles.add(n);
            }
        }

        else
        {
            for (Node n : possibleNodes)
            {
                List<Node> children = getChildren(n);
                for (Node child : children)
                {
                    Person c = (Person) child.data;
                    if (c.name.equals(post))
                        possibles.add(n);
                }
            }
        }

        return possibles;
    }

    /**
     * This method add new child to tree
     * @param toAdd to be added child
     * @param child added child
     */
    private void addChild(Node toAdd, String child)
    {
        Node childNode = new Node(new Person(child, (Person) toAdd.data));

        if (toAdd.left == null)
            toAdd.left = childNode;

        else
        {
            Node temp = toAdd.left;

            while (temp.right != null)
                temp = temp.right;

            temp.right = childNode;
        }

    }

    /**
     * This method finds all nodes that matches wtih the name recursively
     * @param name name for looking
     * @param node node for looking
     * @param results matched nodes
     */
    private void findByName(String name, Node node, List<Node> results)
    {
        if (node != null)
        {
            Person p = (Person) node.data;
            if (p.name.equals(name))
                results.add(node);

            findByName(name, node.left, results);
            findByName(name, node.right, results);
        }
    }

    /**
     * This method finds a node
     * @param name name to be searched
     * @param node node to be searched
     * @return founded node( null if doesnt exist)
     */
    private Node findANode(String name, Node node)
    {
        if (node != null)
        {
            Person p = (Person) node.data;
            //System.out.println(name + " - " + p.name);
            if (p.name.equals(name))
                return node;

            Node t = findANode(name, node.left);
            if (t != null)
                return t;
            t = findANode(name, node.right);
            if (t != null)
                return t;
        }

        return null;
    }

    /**
     * This method finds all children of a parent
     * @param node parent node
     * @return all child
     */
    private List<Node> getChildren(Node node)
    {
        if (node == null)
            return null;

        List<Node> children = new ArrayList<Node>();
        Node temp = node.left;

        while (temp != null)
        {
            children.add(temp);
            temp = temp.right;
        }

        return children;
    }

    /**
     * Implementaiton iterator
     * @return iterator
     */
    public Iterator iterator()
    {
        return new FamilyTreeIterator(root);
    }

    /**
     * Level order iterator for the family tree.
     * @return iterator
     */
    public Iterator levelOrderIterator()
    {
        return new MyLevelOrderIterator(root);
    }

    /**
     * Implementation of iterator for familly tree
     */
    private class FamilyTreeIterator implements Iterator
    {

        List<Node> nodes = new ArrayList<Node>();
        int index = 0;
        int size = -1;

        public FamilyTreeIterator(Node root)
        {
            this.size = numOfNodes(root);
            nodes.add(root);
            getData();
            index = 0;
        }

        private void getData()
        {
            Node n = nodes.get(index);

            Node temp = n.left;
            while (temp != null)
            {
                nodes.add(temp);
                temp = temp.right;
            }

            index += 1;
            if (index != (size-1))
                getData();
        }

        private int numOfNodes(Node from)
        {
            if (from != null)
                return 1 + numOfNodes(from.left) + numOfNodes(from.right);

            return 0;
        }

        @Override
        public boolean hasNext()
        {
            return index < nodes.size();
        }

        @Override
        public Object next()
        {
            if (!hasNext())
                throw new NoSuchElementException();

            Person p = (Person) nodes.get(index).data;
            index++;
            return p.name;
        }
    }

    private class Person
    {
        Person(String name, Person parent)
        {
            this.name = name;
            this.parent = parent;
        }

        String name = "";
        Person parent;

        @Override
        public String toString()
        {
            return name;
        }
    }

    private class MyLevelOrderIterator<E> implements Iterator<E>
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