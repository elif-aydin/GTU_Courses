package methods;

/**
 * A concrete Method implementation that contains MatrixInversion logic.
 */
public class MatrixInversion implements Method
{
    /**
     * Implementation of "Method Interface" as MatrixInversion.
     * @param matrix Matrix to be solved
     * @return The result as String
     */
    @Override
    public String solve(double[][] matrix)
    {
        // We are getting constants of equations as a separate array
        double [][]constants = new double[matrix.length][1];
        for (int i = 0; i < matrix.length; ++i)
        {
            double[] arr = matrix[i];
            constants[i][0] = arr[arr.length - 1];
        }

        // Building array again without constants
        double[][] matrix2 = new double[matrix.length][matrix.length];
        for (int i = 0; i < matrix.length; ++i)
        {
            for (int j = 0; j < matrix[0].length - 1; ++j)
            {
                matrix2[i][j] = matrix[i][j];
            }
        }

        ///////////////
        int n = matrix2.length;
        double invertedMatrix[][] = new double[n][n];
        double b[][] = new double[n][n];
        int index[] = new int[n];
        for (int i = 0; i < n; ++i)
            b[i][i] = 1;

        // apply gaussian to transform.
        gaussian(matrix2, index);

        for (int i = 0; i < n - 1; ++i)
            for (int j = i + 1; j < n; ++j)
                for (int k = 0; k < n; ++k)
                    b[index[j]][k] -= (matrix2[index[j]][i] * b[index[i]][k]);

        for (int i = 0; i < n; ++i)
        {
            invertedMatrix[n-1][i] = (b[index[n - 1]][i] / matrix2[index[n - 1]][n - 1]);
            for (int j = n - 2; j >= 0; --j)
            {
                invertedMatrix[j][i] = b[index[j]][i];
                for (int k = j + 1; k < n; ++k)
                {
                    invertedMatrix[j][i] -= matrix2[index[j]][k] * invertedMatrix[k][i];
                }
                invertedMatrix[j][i] /= matrix2[index[j]][j];
            }
        }

        ////////////////

        double result[][] = new double[matrix2.length][1];
        for (int i = 0; i < matrix2.length; i++)
        {
            for (int j = 0; j < 1; j++)
            {
                for (int k = 0; k < matrix2.length; k++)
                {
                    // multiply inverted matrix with constants of equations
                    result[i][j] = result[i][j] + invertedMatrix[i][k] * constants[k][j];
                }
            }
        }

        // collect the results
        StringBuilder sb = new StringBuilder("Solution: ");
        for (int i = 0; i < result.length; i++)
        {
            sb.append("x").append(i+1).append(" = ").append(String.format("%.7f", result[i][0])).append("\n");
        }

        return sb.toString();
    }

    /**
     * Method to apply Gaussian elimination to a matrix.
     * @param a the original matrix
     * @param index pivots
     */
    private void gaussian(double a[][], int index[])
    {
        int size = index.length;
        double c[] = new double[size];

        for (int i = 0; i < size; ++i)
            index[i] = i;

        for (int i = 0; i < size; ++i)
        {
            double c1 = 0;
            for (int j = 0; j < size; ++j)
            {
                double c0 = Math.abs(a[i][j]);
                if (c0 > c1)
                    c1 = c0;
            }
            c[i] = c1;
        }

        int k = 0;
        for (int j = 0; j < size-1; ++j)
        {
            double pi1 = 0;
            for (int i = j; i < size; ++i)
            {
                double pi0 = Math.abs(a[index[i]][j]);
                pi0 /= c[index[i]];
                if (pi0 > pi1)
                {
                    pi1 = pi0;
                    k = i;
                }
            }

            int temp = index[j];
            index[j] = index[k];
            index[k] = temp;
            for (int i = j + 1; i < size; ++i)
            {
                double pj = (a[index[i]][j] / a[index[j]][j]);
                a[index[i]][j] = pj;
                for (int l = j + 1; l < size; ++l)
                    a[index[i]][l] -= pj*a[index[j]][l];
            }
        }
    }
}
