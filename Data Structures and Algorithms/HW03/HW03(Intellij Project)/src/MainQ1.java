import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

/**
 * Created by elif on 13-Mar-17.
 */
public class MainQ1
{
    private final static String numberTxt = "numbers.txt";
    private final static String result1Txt = "result1.txt";
    private final static String result2Txt = "result2.txt";
    private final static String result3Txt = "result3.txt";

    public static void main(String[] args) throws IOException
    {
        String line ;
        MyStringBuilder msb = new MyStringBuilder();


        try(BufferedReader br = new BufferedReader(new FileReader(numberTxt)))
        {
            System.out.println("Reading 100000 numbers.");
            while((line = br.readLine()) != null)
            {
                int a = Integer.parseInt(line);
                msb.append(a);
            }

            System.out.println("Started");

            long start1 = System.currentTimeMillis(); // for timer

            FileWriter fileWriter1 = new FileWriter(result1Txt);
            fileWriter1.write(msb.toStringWithIndexes());

            fileWriter1.close();

            long total1 = System.currentTimeMillis() - start1;
            System.out.println("Time for indexes and get method");
            System.out.println("ms: " + total1);
            System.out.println("second: " + Math.round(total1 / 1000L));


            long start2 = System.currentTimeMillis(); // for timer

            FileWriter fileWriter2 = new FileWriter(result2Txt);
            fileWriter2.write(msb.toStringWithIterator());

            fileWriter2.close();

            long total2 = System.currentTimeMillis() - start2;
            System.out.println("\nTime for iterator ");
            System.out.println("ms: " + total2);
            System.out.println("second: " + Math.round(total2 / 1000L));


            long start3 = System.currentTimeMillis(); // for timer

            FileWriter fileWriter3 = new FileWriter(result3Txt);
            fileWriter3.write(msb.toString());

            fileWriter3.close();

            long total3 = System.currentTimeMillis() - start3;
            System.out.println("\nTime for toString");
            System.out.println("ms: " + total3);
            System.out.println("second: " + Math.round(total3 / 1000L));
        }
        catch(IOException e)
        {
            System.err.println("numbers.txt is missing.\n");
            throw e;
        }
    }
}
