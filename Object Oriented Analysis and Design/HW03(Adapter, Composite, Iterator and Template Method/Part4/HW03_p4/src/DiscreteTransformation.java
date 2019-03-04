import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

/**
 * The abstract class for the Template method. Contains the IO operations and main algorithm for calculations.
 */
public abstract class DiscreteTransformation {

    private long elapsedTime;
    protected double[] inputData;
    protected double[] outputData;

    /**
     * The template method. Contains the program logic.
     * @param inputFile file to read inputs.
     * @param outputFile file to write results.
     * @return the result
     * @throws IOException
     */
    public double[] calculateTransformation(String inputFile, String outputFile) throws IOException {

        readFromFile(inputFile);
        long start = System.nanoTime();
        transformation();
        elapsedTime = System.nanoTime() - start;
        writeToFile(outputFile);

        afterHook();

        return outputData;
    }

    /**
     * Reads input data from given file.
     * @param fileName  file to read data.
     * @return  number of lines in the file.
     * @throws IOException
     */
    private int readFromFile(String fileName) throws IOException {
        int counter = 0;
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            String line = br.readLine();
            inputData = new double[Integer.parseInt(line)];
            outputData = new double[inputData.length];
            while ((line = br.readLine()) != null) {
                inputData[counter++] = Double.parseDouble(line);
            }
        }
        return counter;
    }

    /**
     * The calculation step. Each algorithm should implement this.
     * @return
     */
    protected abstract double[] transformation();

    /**
     * Writes the result to the given file.
     * @param fileName file to write.
     * @return  Success or fail status of writing.
     * @throws IOException
     */
    private boolean writeToFile(String fileName) throws IOException {
        FileWriter fw = new FileWriter(fileName);

        for (int i = 0; i < outputData.length; i++) {
            fw.write(Double.toString(outputData[i]));
            fw.write("\n");
        }

        fw.close();
        return true;
    }

    /**
     *  A hook method for the template method. Calling after the calculations. Default to empty.
     */
    protected void afterHook()
    {
        // empty
    }

    /**
     * Gets the elapsed time of calculation.
     * @return elapsed time of calculation.
     */
    public long getElapsedTime() {
        return elapsedTime;
    }
}
