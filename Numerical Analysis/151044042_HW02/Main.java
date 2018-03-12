import java.util.ArrayList;

/**
 * Created by elif on 07-Apr-17.
 */
public class Main
{
    public static void main(String[] args) throws Exception
    {
        if (args.length != 4)
        {
            throw new IllegalArgumentException("Usage: $./solver -i system.txt -m GESP");
        }

        String pre = args[0];
        String fileName = args[1];
        String m = args[2];
        String methodName = args[3];

        if (!pre.equals("-i") || !m.equals("-m"))
            throw new IllegalArgumentException("Usage: $./solver -i system.txt -m GESP");

        if(methodName.equals("GESP"))
        {
            GaussianElimination gauss = new GaussianElimination();

            ArrayList<String> matrix = gauss.fileToString(fileName);
            double[][] arr = gauss.stringToDoubleArray(matrix);

            System.out.println("\n Our Matrix before Gaussian Elimination: ");
            gauss.printEquation(arr);
            gauss.gaussianElimination(arr);
            gauss.showResult(arr);
        }

        else if(methodName.equals("JCB"))
        {
            throw new UnsupportedOperationException("I couldn't implement Jacobi's method, sorry :(");
        }
    }
}
