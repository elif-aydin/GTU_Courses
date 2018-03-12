import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.io.File;
import java.util.Iterator;

/**
 * Created by elif on 04-Apr-17.
 */
public class MainQ1_2
{
    private static ArrayList<Integer> fileArray = new ArrayList<Integer>();

    private final static String fileName = "test.txt";
    private final static String splitter = "\\s+";

    public static void main(String[] args) throws Exception
    {
        readFile();
        BinarySearchTree<Integer> tree = new BinarySearchTree<Integer>();

        //Agacimiz test.txt dosyasindan olusturulmustur.
        for (int i = 0; i < fileArray.size(); i++)
            tree.add(fileArray.get(i));

        System.out.println("Binary Search Tree :\n\n");
        TreePrinter.printNode(tree.root);

        System.out.println("\nLevel-Order Traversal :\n");
        Iterator it = tree.iterator();
        while (it.hasNext())
            System.out.print(it.next() + " ");

        System.out.println("\n");
    }

    private static void readFile() throws Exception
    {
        BufferedReader br = new BufferedReader(new FileReader(new File(fileName)));
        String line = br.readLine();
        String[] tokens = line.split(splitter);
        ArrayList<String> temp = new ArrayList<String>();

        for (int i = 0; i < tokens.length; i++)
            temp.add(tokens[i]);

        for (int i = 0; i < temp.size(); i++) //Okunan dosyadaki stringleri int e cevirme
            fileArray.add(Integer.parseInt(temp.get(i)));
    }


}


