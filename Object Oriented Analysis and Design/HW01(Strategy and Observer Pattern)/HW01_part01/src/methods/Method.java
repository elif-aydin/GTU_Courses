package methods;

/**
 * This interface is "Strategy" component of Strategy Pattern.
 * It includes the method that concrete methods should implement.
 */
public interface Method
{
    /**
     * The common method for all concrete implementations of methods. Solves the linear equations.
     * @param matrix Matrix to be solved
     * @return The result as a string
     */
    public String solve(double [][] matrix);
}
