import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

/**
 * Created by elif on 22-Mar-17.
 */
public class MainQ2
{
    private static ArrayList<String[]> fileArray = new ArrayList<>();

    private final static String testCsv = "test.csv";
    private final static String splitter = ","; // Csv dosyasini ayirmak icin


    public static void main(String[] args) throws Exception
    {
        readFile();

        MyQueue<Integer> myQueueInt = new MyQueue<>();
        Queue<Integer> intQ = new LinkedList<>();

        MyQueue<Float> myQueueFlo = new MyQueue<>();
        Queue<Float> floatQ = new LinkedList<>();

        MyQueue<Character> myQueueChar = new MyQueue<>();
        Queue<Character> charQ = new LinkedList<>();

        MyQueue<String> myQueueStr = new MyQueue<>();
        Queue<String> strQ = new LinkedList<>();


        for (int i = 0; i < fileArray.get(0).length ; i++)
        {
            myQueueInt.offer((Integer.parseInt(fileArray.get(0)[i])));
            intQ.offer((Integer.parseInt(fileArray.get(0)[i])));
        }

        //////////////////////////////////////////////////

        for (int i = 0; i < fileArray.get(1).length ; i++)
        {
            myQueueFlo.offer((Float.parseFloat(fileArray.get(1)[i])));
            floatQ.offer((Float.parseFloat(fileArray.get(1)[i])));
        }

        //////////////////////////////////////////////////


        for (int i = 0; i < fileArray.get(2).length ; i++)
        {
            myQueueChar.offer(fileArray.get(2)[i].charAt(0));
            charQ.offer(fileArray.get(2)[i].charAt(0));
        }

        //////////////////////////////////////////////////


        for (int i = 0; i < fileArray.get(3).length ; i++)
        {
            myQueueStr.offer(fileArray.get(3)[i]);
            strQ.offer(fileArray.get(3)[i]);
        }

        List<String> resultList = new ArrayList<>();

        long start1 = System.nanoTime(); // for timer

        myQueueStr.reverse();
        resultList.add(myQueueStr.toString());

        myQueueChar.reverse();
        resultList.add(myQueueChar.toString());

        myQueueFlo.reverse();
        resultList.add(myQueueFlo.toString());


        myQueueInt.reverse();
        resultList.add(myQueueInt.toString());

        long total1 = System.nanoTime() - start1;
        System.out.println("\nTime for Iterative reverse: ");
        System.out.println("nano second: " + total1);

//////////////////////////////////////////

        long start2 = System.nanoTime(); // for timer

        reverseQueue(strQ);
        reverseQueue(charQ);
        reverseQueue(floatQ);
        reverseQueue(intQ);

        resultList.add(strQ.toString().replace("[", "").replace("]", "").replaceAll(" ", ""));
        resultList.add(charQ.toString().replace("[", "").replace("]", "").replaceAll(" ", ""));
        resultList.add(floatQ.toString().replace("[", "").replace("]", "").replaceAll(" ", ""));
        resultList.add(intQ.toString().replace("[", "").replace("]", "").replaceAll(" ", ""));

        long total2= System.nanoTime() - start2;
        System.out.println("\nTime for Recursive reverse: ");
        System.out.println("nano second: " + total2);


        try
        {
            FileWriter writer = new FileWriter("testResult_2.csv");
            for (String s : resultList)
                writer.write(s + "\n");
            writer.close();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }


    public static void reverseQueue(Queue queue)
    {
        if(queue.isEmpty())
            return;

        Object A = queue.poll();
        reverseQueue(queue);

        queue.offer(A);
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
