import methods.GaussianElimination;
import methods.Method;

/**
 * This class is "Client" component of Strategy Pattern.
 * Uses concrete implementations to serve the user.
 * It includes the method that executes the chosen methods logic and a setter to change the concrete implementation.
 */
public class LinearEquationSolver
{
    /**
     *  A concrete "Strategy Method" that a user can change any time.
     */
    private Method method = null;

    /**
     *  Default constructor of this class. Assigns default method as GaussianElimination.
     */
    public LinearEquationSolver()
    {
        this.method = new GaussianElimination();
    }

    /**
     *  Method to set the concrete Method.
     * @param method Method to set
     */
    public void setMethod(Method method)
    {
        this.method = method;
    }

    /**
     *  Method to execute the chosen concrete Method's logic.
     * @param matrix Matrix to execute
     * @return The result as a string
     */
    public String executeMethod(double [][] matrix)
    {
        return method.solve(matrix);
    }
}
