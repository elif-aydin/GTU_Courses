import java.io.Serializable;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;

/** Class to represent and build a Huffman tree.
 *   @author Koffman and Wolfgang
 * */

public class HuffmanTree implements Serializable
{
    // Nested Classes
    /** A datum in the Huffman tree. */
    public static class HuffData implements Serializable
    {
        // Data Fields
        /** The weight or probability assigned to this HuffData. */
        private double weight;

        /** The alphabet symbol if this is a leaf. */
        private Character symbol;

        public HuffData(double weight, Character symbol)
        {
            this.weight = weight;
            this.symbol = symbol;
        }

        @Override
        public boolean equals(Object obj)
        {
            HuffData h = (HuffData) obj;
            return h.weight == this.weight;
        }

        @Override
        public String toString()
        {
            return symbol + "-" + weight;
        }
    }

    // Data Fields
    /** A reference to the completed Huffman tree. */
    public BinaryTree < HuffData > huffTree;

    /** A Comparator for Huffman trees; nested class. */
    private static class CompareHuffmanTrees implements Comparator< BinaryTree < HuffData >>
    {
        /** Compare two objects.
         @param treeLeft The left-hand object
         @param treeRight The right-hand object
         @return -1 if left less than right,
         0 if left equals right,
         and +1 if left greater than right
         */
        public int compare(BinaryTree <HuffData> treeLeft, BinaryTree <HuffData> treeRight)
        {
            double wLeft = treeLeft.getData().weight;
            double wRight = treeRight.getData().weight;
            return Double.compare(wLeft, wRight);
        }
    }

    /** Builds the Huffman tree using the given alphabet and weights.
     post:  huffTree contains a reference to the Huffman tree.
     @param symbols An array of HuffData objects
     */
    public void buildTree(HuffData[] symbols)
    {
        Queue< BinaryTree <HuffData>> theQueue = new PriorityQueue <BinaryTree <HuffData>> (symbols.length, new CompareHuffmanTrees());
        // Load the queue with the leaves.
        for (HuffData nextSymbol : symbols)
        {
            BinaryTree <HuffData> aBinaryTree = new BinaryTree <HuffData> (nextSymbol, null, null);
            theQueue.offer(aBinaryTree);
        }

        // Build the tree.
        while (theQueue.size() > 1)
        {
            BinaryTree <HuffData> left = theQueue.poll();
            BinaryTree <HuffData> right = theQueue.poll();
            double wl = left.getData().weight;
            double wr = right.getData().weight;
            HuffData sum = new HuffData(wl + wr, null);
            BinaryTree <HuffData> newTree = new BinaryTree < HuffData > (sum, left, right);
            theQueue.offer(newTree);
        }

        // The queue should now contain only one item.
        huffTree = theQueue.poll();
    }

    /** Method to decode a message that is input as a string of
     digit characters '0' and '1'.
     @param codedMessage The input message as a String of
     zeros and ones.
     @return The decoded message as a String
     */
    public String decode(String codedMessage)
    {
        StringBuilder result = new StringBuilder();
        BinaryTree <HuffData> currentTree = huffTree;
        for (int i = 0; i < codedMessage.length(); i++)
        {
            if (codedMessage.charAt(i) == '1')
            {
                currentTree = currentTree.getRightSubtree();
            }
            else
            {
                currentTree = currentTree.getLeftSubtree();
            }
            if (currentTree.isLeaf())
            {
                HuffData theData = currentTree.getData();
                result.append(theData.symbol);
                currentTree = huffTree;
            }
        }
        return result.toString();
    }

    /**
     * Gets bit version of character
     * @param localTree tree to be search
     * @param chr chr to be get bit
     * @param stringBuilder keeps bits
     * @return true or false
     */
    private boolean getBits(BinaryTree< HuffData > localTree, Character chr, StringBuilder stringBuilder)
    {
        if (localTree == null)
            return false;
        else if (!localTree.isLeaf()) {
            boolean res = getBits(localTree.getLeftSubtree(), chr, stringBuilder);
            if (res)
            {
                stringBuilder.append("0");
                return true;
            }
            else if (getBits(localTree.getRightSubtree(), chr, stringBuilder))
            {
                stringBuilder.append("1");
                return true;
            }
            else return false;
        }
        else if (localTree.getData().symbol.equals(chr))
        {
            return true;
        }
        else return false;
    }

    /**
     * this method encode the given string
     * @param message stirng to be encode
     * @return encoded string
     */
    public String encode(String message)
    {
        StringBuilder sb = new StringBuilder();
        for (char ch : message.toCharArray())
        {
                StringBuilder sb2 = new StringBuilder();
                getBits(huffTree, ch, sb2);
                sb.append(sb2.reverse().toString());
        }

        return sb.toString();
    }
}