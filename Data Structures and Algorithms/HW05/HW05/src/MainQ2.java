import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Iterator;

/**
 * Created by elif on 06-Apr-17.
 */
public class MainQ2
{
    private static ArrayList<String> fileArray = new ArrayList<String>();
    private final static String fileName = "family.txt";
    private final static String splitter = ",";


    public static void main(String[] args) throws Exception
    {
        readFile();
        String root = fileArray.get(0).trim();
        FamilyTree familyTree = new FamilyTree(root);
        String[] temp;

        for (int i = 1; i < fileArray.size() ; i++)
        {
            temp = fileArray.get(i).split(splitter);
            familyTree.add(temp[0].trim(), temp[1].trim(), temp[2].trim());
        }

        TreePrinter.printNode(familyTree.root);
        Iterator iter = familyTree.iterator();

        System.out.println("\nCorrectly iterator for family tree \n");
        while (iter.hasNext())
        {
            System.out.println(iter.next());
        }
    }

    public static void readFile() throws Exception
    {
        BufferedReader br = new BufferedReader(new FileReader(new File(fileName)));
        String temp = br.readLine();
        while (temp != null)
        {
            fileArray.add(temp);
            temp = br.readLine();
        }
    }
}



