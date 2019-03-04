import java.util.Arrays;
import java.util.Iterator;

public class Main {

    public static void main(String[] args) {

        int[][] arr = new int[][]
        {
                {1, 2, 3, 4, 20, 21},
                {5, 6, 7, 8, 30 , 33 },
                {9, 10, 11, 12, 25, 26},
                {13, 14, 15, 16, 29, 31}
        };
        System.out.println("The test data : ");
        for (int[] anArr : arr)
            System.out.println(Arrays.toString(anArr));
        System.out.println();

        Iterator it = new ClockwiseIterator(arr);
        System.out.println("Result : ");
        while (it.hasNext())
        {
            System.out.println(it.next());
        }
    }
}
