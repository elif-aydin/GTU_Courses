import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;

/**
 * Created by elif on 22-Mar-17.
 */
public class MainQ3
{
    private static ArrayList<String[]> fileArray = new ArrayList<>();

    private final static String testCsv = "test.csv";
    private final static String splitter = ","; // Csv dosyasini ayirmak icin


    public static void main(String[] args) throws Exception
    {

        List<String> resultList = new ArrayList<>();

        readFile();
///////////////////////////////////////////////////////////////////////////////

        long start1 = System.nanoTime(); // for timer


        PriorityQueueA<Integer> priorityQueueAInt = new PriorityQueueA<>();

        for (int i = 0; i < fileArray.get(0).length ; i++)
        {
            priorityQueueAInt.insert((Integer.parseInt(fileArray.get(0)[i])));
        }


        PriorityQueueA<Float> priorityQueueAFlo = new PriorityQueueA<>();

        for (int i = 0; i < fileArray.get(1).length ; i++)
        {
            priorityQueueAFlo.insert((Float.parseFloat(fileArray.get(1)[i])));
        }


        PriorityQueueA<Character> priorityQueueAChar = new PriorityQueueA<>();


        for (int i = 0; i < fileArray.get(2).length ; i++)
        {
            priorityQueueAChar.insert(fileArray.get(2)[i].charAt(0));
        }


        PriorityQueueA<String> priorityQueueAStr = new PriorityQueueA<>();

        for (int i = 0; i < fileArray.get(3).length ; i++)
        {
            priorityQueueAStr.insert(fileArray.get(3)[i]);
        }

        resultList.add(priorityQueueAInt.toString());
        resultList.add(priorityQueueAFlo.toString());
        resultList.add(priorityQueueAChar.toString());
        resultList.add(priorityQueueAStr.toString());

        long total1 = System.nanoTime() - start1;
        System.out.println("Time for PriorityQueueA:");
        System.out.println("nano second: " + total1);

        ////////////////////////////////////////////////////////////////////

        long start2 = System.nanoTime(); // for timer


        PriorityQueueB<Integer> priorityQueueBInt = new PriorityQueueB<>();


        for (int i = 0; i < fileArray.get(0).length ; i++)
        {
            priorityQueueBInt.insert((Integer.parseInt(fileArray.get(0)[i])));
        }

        PriorityQueueB<Float> priorityQueueBFlo = new PriorityQueueB<>();

        for (int i = 0; i < fileArray.get(1).length ; i++)
        {
            priorityQueueBFlo.insert((Float.parseFloat(fileArray.get(1)[i])));
        }


        PriorityQueueB<Character> priorityQueueBChar = new PriorityQueueB<>();


        for (int i = 0; i < fileArray.get(2).length ; i++)
        {
            priorityQueueBChar.insert(fileArray.get(2)[i].charAt(0));
        }


        PriorityQueueB<String> priorityQueueBStr = new PriorityQueueB<>();

        for (int i = 0; i < fileArray.get(3).length ; i++)
        {
            priorityQueueBStr.insert(fileArray.get(3)[i]);
        }

        resultList.add(priorityQueueBInt.toString());
        resultList.add(priorityQueueBFlo.toString());
        resultList.add(priorityQueueBChar.toString());
        resultList.add(priorityQueueBStr.toString());


        long total2 = System.nanoTime() - start2;
        System.out.println("\nTime for PriorityQueueB: ");
        System.out.println("nano seoond: " + total2);

        ////////////////////////////////////////////////////////////////////////


        try
        {
            FileWriter writer = new FileWriter("testResult_3.csv");
            for (String s : resultList)
                writer.write(s + "\n");
            writer.close();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }


    private static void readFile() throws Exception
    {
        String line; //Dosyayi okuyacagimiz string

        try(BufferedReader br = new BufferedReader(new FileReader(testCsv)))
        {
            while ((line = br.readLine()) != null)
                fileArray.add(line.split(splitter));
        }
        catch (IOException e)
        {
            System.out.println("test.csv is missing.");
            throw e;
        }
    }



}
