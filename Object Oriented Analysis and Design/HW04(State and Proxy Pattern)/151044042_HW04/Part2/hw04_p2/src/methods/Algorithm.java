package methods;

/**
 * Interface to represent each method that this program supports.
 */
public interface Algorithm {
	/**
	 * Runs this method's algorithm.
	 */
	void execute();

	/**
	 * Extracts the result from the data that generated from execute() method.
	 * @return	method's result as Result object
	 */
	Result getResult();
	
}