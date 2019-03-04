import java.io.IOException;
import java.util.Scanner;

public class Main
{

    public static void main(String[] args) throws IOException {

        Scanner in = new Scanner(System.in);

        System.out.print("Input file: ");
        String inputFile = in.nextLine();

        System.out.println("Running cosine: ");
        DiscreteTransformation coss = new DiscreteCosineTransform();
        coss.calculateTransformation(inputFile, "out_cosine.txt");
        System.out.println("Done cosine.");

        System.out.println("Running fourier: ");
        DiscreteTransformation fourr = new DiscreteFourierTransform();
        fourr.calculateTransformation(inputFile, "out_four.txt");
        System.out.println("Done fourier.");
    }
}
