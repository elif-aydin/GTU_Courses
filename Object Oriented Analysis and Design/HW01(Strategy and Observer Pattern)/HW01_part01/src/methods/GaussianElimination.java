package methods;

/**
 * A concrete Method implementation that contains GaussianElimination logic.
 */
public class GaussianElimination implements Method
{
    /**
     * Implementation of "Method Interface" as GaussianElimination.
     * @param matrix Matrix to be solved
     * @return The result as String
     */
    @Override
    public String solve(double[][] matrix)
    {
        eliminateMatrix(matrix);
        reverseMatrix(matrix);

        StringBuilder sb = new StringBuilder("Solution: ");

        for (int i = 0; i < matrix.length; i++)
        {
            sb.append("x").append(i+1).append(" = ").append(String.format("%.5f", matrix[i][matrix[i].length - 1])).append("\n");
        }

        return sb.toString();
    }

    /**
     * Method to eliminate the input matrix.
     * @param matrix to be eliminated
     */
    private  void eliminateMatrix(double[][] matrix)
    {
        for (int k = 0; k < (matrix.length - 1); k++)
        {
            for (int i = k + 1; i < matrix.length; i++)
                for ( int j = matrix.length; j >= k; j--)
                    matrix[i][j] = matrix[i][j] - matrix[i][k] * matrix[k][j] / matrix[k][k];
        }
    }

    /**
     * Reverses a given matrix.
     * @param matrix to be reversed
     */
    private void reverseMatrix(double[][] matrix)
    {
        double sum ;
        for (int i = matrix.length - 1; i >= 0; i--)
        {
            sum = 0;
            for ( int j = matrix.length - 1; j >= i + 1; j--)
                sum += matrix[i][j] * matrix[j][matrix.length];

            matrix[i][matrix.length] = (matrix[i][matrix.length] - sum) / matrix[i][i];
        }
    }
}
