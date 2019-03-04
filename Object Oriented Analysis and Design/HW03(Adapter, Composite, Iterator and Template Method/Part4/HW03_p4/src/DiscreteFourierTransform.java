/**
 * A class to implement Fourier transformation that extends the DiscreteTransformation (Template Method)
 */
public class DiscreteFourierTransform extends DiscreteTransformation {

    /**
     * The calculation step of Fourier transformation. Other steps implemented in super.
     * @return the calculated result.
     */
    @Override
    public double[] transformation() {
        int size = inputData.length;
        for (int k = 0; k < size; k+= 2) {
            double sumreal = 0;
            double sumimag = 0;
            for (int t = 0; t < size; t+= 2) {
                double angle = 2 * Math.PI * t * k / size;
                sumreal +=  inputData[t] * Math.cos(angle) + inputData[t + 1] * Math.sin(angle);
                sumimag += -inputData[t] * Math.sin(angle) + inputData[t + 1] * Math.cos(angle);
            }
            outputData[k] = sumreal;
            outputData[k + 1] = sumimag;
        }

        return outputData;
    }

    /**
     * The hook implementation that will be called by super after the calculation.
     */
    @Override
    public void afterHook() {
        System.out.println("Elapsed time in nano: " + this.getElapsedTime());
    }
}
