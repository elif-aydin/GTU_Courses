/**
 * A class to implement cosine transformation that extends the DiscreteTransformation (Template Method)
 */
public class DiscreteCosineTransform extends DiscreteTransformation {

    /**
     * The calculation step of cosine transformation. Other steps implemented in super.
     * @return the calculated result.
     */
    @Override
    public double[] transformation() {
        double factor = Math.PI / inputData.length;
        for (int i = 0; i < inputData.length; i++) {
            double sum = 0;
            for (int j = 0; j < inputData.length; j++)
                sum += inputData[j] * Math.cos((j + 0.5) * i * factor);
            outputData[i] = sum;
        }
        return outputData;
    }
}
