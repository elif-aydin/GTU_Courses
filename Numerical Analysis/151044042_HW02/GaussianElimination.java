import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;


public class GaussianElimination
{

    public static void gaussianElimination(double[][] arr)
    {
        eliminateMatrix(arr);
        reverseMatrix(arr);
    }

    private static void eliminateMatrix(double[][] arr)
    {
        for (int k = 0; k < arr.length - 1; k++)
        {
            for (int i = k + 1; i < arr.length; i++)
                for ( int j = arr.length; j >= k; j--)
                    arr[i][j] = arr[i][j] - arr[i][k] * arr[k][j] / arr[k][k];
        }
    }

    private static void reverseMatrix(double[][] arr)
    {
    	double sum ;

        for (int i = arr.length - 1; i >= 0; i--)
        {
        	sum = 0;
            for ( int j = arr.length - 1; j >= i + 1; j--)
                sum += arr[i][j] * arr[j][arr.length];
            
            arr[i][arr.length] = (arr[i][arr.length] - sum) / arr[i][i];
        }
    }

    public static void printEquation(double[][] arr)
    {
        for (int i = 0; i < arr.length; i++)
        {
            // i satiri basilir
            for (int j = 0; j < arr.length; j++)
            {
                if ( j != 0 )
                    System.out.print(" + ");

                System.out.print(arr[i][j] + " x" + (j+1));
            }

            System.out.println(" = " + arr[i][arr[i].length - 1]);
        }

        System.out.println();
    }

    public static double[][] stringToDoubleArray(ArrayList<String> matrix)
    {
        // String i double array e çeviririz
        int n = matrix.size();
        double[][] arr = new double[n][n + 1];

        for (int i=0; i < n; i++)
        {
            String [] parts = matrix.get(i).split(",");
            for (int j = 0; j < n + 1; j++)
                arr[i][j] = Double.parseDouble(parts[j]);
        }
        return arr;
    }

    public static void showResult(double[][] arr)
    {
        StringBuilder sb = new StringBuilder("Solution:\n");

        for (int i = 0; i < arr.length; i++)
        {
        	sb.append("x").append(i+1).append(" = ").append(Math.round(arr[i][arr[i].length - 1] * 100.0 ) / 100.0).append("\n");
        }

        System.out.println(sb.toString());
    }

    public static ArrayList<String> fileToString(String fileName) throws Exception
    {
        //method transform text from file to an Arraylist. Every element of array is one line of text
        Scanner scanner = new Scanner(new File(fileName));

            ArrayList<String> list = new ArrayList <String>();
            if (scanner != null)
            {
                while (scanner.hasNext())
                    list.add(scanner.next());

                scanner.close();
            }
            return list;
        }

}