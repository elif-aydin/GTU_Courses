import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by elif on 22-Mar-17.
 */
public class MainQ1
{
    private static ArrayList<String[]> fileArray = new ArrayList<>();

    private final static String testCsv = "test.csv";
    private final static String splitter = ","; // Csv dosyasini ayirmak icin


    public static void main(String[] args) throws Exception
    {
        readFile();

        StackA<Integer> stackAInt = new StackA<>();
        StackB<Integer> stackBInt = new StackB<>();
        StackC<Integer> stackCInt = new StackC<>();
        StackD<Integer> stackDInt = new StackD<>();

        StackA<Float> stackAFlo = new StackA<>();
        StackB<Float> stackBFlo = new StackB<>();
        StackC<Float> stackCFlo = new StackC<>();
        StackD<Float> stackDFlo = new StackD<>();

        StackA<Character> stackAChar = new StackA<>();
        StackB<Character> stackBChar = new StackB<>();
        StackC<Character> stackCChar = new StackC<>();
        StackD<Character> stackDChar = new StackD<>();

        StackA<String> stackAStr = new StackA<>();
        StackB<String> stackBStr = new StackB<>();
        StackC<String> stackCStr = new StackC<>();
        StackD<String> stackDStr = new StackD<>();

        List<String> resultList = new ArrayList<>();

////////////////////////////////////////////////////////////////////////////

        long start1 = System.nanoTime(); // for timer
        getIntegers(stackAInt, fileArray.get(0));
        getFloats(stackAFlo, fileArray.get(1));
        getChars(stackAChar, fileArray.get(2));
        getStrs(stackAStr, fileArray.get(3));

        resultList.add(stackAInt.size() + "," + stackAInt.toString());
        resultList.add(stackAFlo.size() + "," + stackAFlo.toString());
        resultList.add(stackAChar.size() + "," + stackAChar.toString());
        resultList.add(stackAStr.size() + "," + stackAStr.toString());

        long total1 = System.nanoTime() - start1;
        System.out.println("Time for StackA:");
        System.out.println("nano second: " + total1);

/////////////////////////////////////////////////////////////////////////////

        long start2 = System.nanoTime(); // for timer

        getIntegers(stackBInt, fileArray.get(0));
        getFloats(stackBFlo, fileArray.get(1));
        getChars(stackBChar, fileArray.get(2));
        getStrs(stackBStr, fileArray.get(3));

        resultList.add(stackBInt.size() + "," + stackBInt.toString());
        resultList.add(stackBFlo.size() + "," + stackBFlo.toString());
        resultList.add(stackBChar.size() + "," + stackBChar.toString());
        resultList.add(stackBStr.size() + "," + stackBStr.toString());

        long total2 = System.nanoTime() - start2;
        System.out.println("\nTime for StackB: ");
        System.out.println("nano seoond: " + total2);


///////////////////////////////////////////////////////////////////////////////

        long start3 = System.nanoTime(); // for timer

        getIntegers(stackCInt, fileArray.get(0));
        getFloats(stackCFlo, fileArray.get(1));
        getChars(stackCChar, fileArray.get(2));
        getStrs(stackCStr, fileArray.get(3));

        resultList.add(stackCInt.size() + "," + stackCInt.toString());
        resultList.add(stackCFlo.size() + "," + stackCFlo.toString());
        resultList.add(stackCChar.size() + "," + stackCChar.toString());
        resultList.add(stackCStr.size() + "," + stackCStr.toString());

        long total3 = System.nanoTime() - start3;
        System.out.println("\nTime for StackC: ");
        System.out.println("nano second: " + total3);

///////////////////////////////////////////////////////////////////////////////

        long start4 = System.nanoTime(); // for timer

        getIntegers(stackDInt, fileArray.get(0));
        getFloats(stackDFlo, fileArray.get(1));
        getChars(stackDChar, fileArray.get(2));
        getStrs(stackDStr, fileArray.get(3));

        resultList.add(stackDInt.size() + "," + stackDInt.toString());
        resultList.add(stackDFlo.size() + "," + stackDFlo.toString());
        resultList.add(stackDChar.size() + "," + stackDChar.toString());
        resultList.add(stackDStr.size() + "," + stackDStr.toString());

        long total4 = System.nanoTime() - start4;
        System.out.println("\nTime for StackD: ");
        System.out.println("nano second: " + total4);

//////////////////////////////////////////////////////////////////////////////////////

        try
        {
            FileWriter writer = new FileWriter("testResult_1.csv");
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


    private static void getIntegers(StackInterface stack, String[] arr)
    {
        for (int i = 0; i < arr.length ; i++)
        {
            stack.push((Integer.parseInt(arr[i])));
        }
    }

    private static void getFloats(StackInterface stack, String[] arr)
    {
        for (int i = 0; i < arr.length ; i++)
        {
            stack.push((Float.parseFloat(arr[i])));
        }
    }

    private static void getChars(StackInterface stack, String[] arr)
    {

        for (int i = 0; i < arr.length ; i++)
        {
            stack.push(arr[i].charAt(0));
        }
    }

    private static void getStrs(StackInterface stack, String[] arr)
    {

        for (int i = 0; i < arr.length ; i++)
        {
            stack.push(arr[i]);
        }
    }

}
