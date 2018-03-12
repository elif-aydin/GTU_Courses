import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by elif on 21-Apr-17.
 */
public class MainQ2
{
    static String[] tests = new String[] {"aba", "alice", "mouse", "i think therefore i am"};

    public static void main(String[] args) throws Exception
    {
        List<HuffmanTree.HuffData> list = new ArrayList<>();
        BufferedReader br = new BufferedReader(new FileReader(new File("freq.txt")));
        String line;
        while ((line = br.readLine()) != null)
        {
            String[] tokens = line.split(" ");
            if (tokens[0].equals("_"))
                tokens[0] = " ";
            list.add(new HuffmanTree.HuffData(Double.parseDouble(tokens[1]), tokens[0].charAt(0)));
        }

        br.close();

        HuffmanTree.HuffData[] data = new HuffmanTree.HuffData[list.size()];
        int i = 0;
        for (HuffmanTree.HuffData d : list)
            data[i++] = d;

        HuffmanTree ht = new HuffmanTree();
        ht.buildTree(data);

        for (String test : tests)
        {
            String e = ht.encode(test);
            String d = ht.decode(e);
            System.out.println("> Text to encoded: " + test + " - " + e);
            System.out.println("  Encoded to decoded: " + e + " - " + d + "\n");
        }
    }


}
