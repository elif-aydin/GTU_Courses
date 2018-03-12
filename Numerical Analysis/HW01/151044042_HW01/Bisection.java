/**
 * Created by elif on 10-Mar-17.
 */

public class Bisection
{
    public static void main(String[] args)
    {
        if(args.length < 4)
        {
            System.out.println("You have to enter 4 input");
            System.out.println("Input 1: the start of the root search interval as a real value: a");
            System.out.println("Input 2: the end of the root search interval as a real value: b");
            System.out.println("Input 3: the type of stopping criterion as a character array (DISTANCE_TO_ROOT,\n" +
                    "ABSOLUTE_ERROR, RELATIVE_ERROR)");
            System.out.println("Input 4: the epsilon value ϵ as a real value");
        }

        double interval1 = Double.parseDouble(args[0]);
        double interval2 = Double.parseDouble(args[1]);
        String stoppingCriteria = args[2];
        double epsilon = Double.parseDouble(args[3]);

        bisectionMethod(interval1,interval2,stoppingCriteria,epsilon);
    }

    public static boolean bisectionMethod(double interval1, double interval2, String stoppingCriteria, double epsilon)
    {
        int iteration = 1;
        double root1, root2;
        double b1 = interval1;
        double b2 = interval2;

        root1 = (interval1 + interval2) / 2;
        System.out.println("ITERATION\t   ABSOLUTE ERROR     RELATIVE ERROR");
        System.out.printf("%3d              %.10f       %.10f\n",iteration,absoluteError(root1,interval1),relativeError(interval1,root1));

        while(iteration <=100)
        {
            double value1 = function(interval1);
            double value2 = function(root1);


            if (value1 * value2 < 0) // eger carpimlari - ise
                b2 = root1; //Yeni araligin ust siniri bizim kokumuz olur. Alt sinir ayni kalir.
            else // Aynı yerdeler ise

                b1 = root1; // Araligin alt siniri kokumuz olur. Ust sinir degismez.

            root2 = (b1 + b2) / 2; // Verilen yeni aralik icin kok bulunur.

            if(errorChecks(stoppingCriteria,root1,root2,epsilon))
            {
                iteration ++;
                System.out.printf("%3d              %.10f       %.10f\n",iteration,absoluteError(root1,root2),relativeError(root1,root2));
                System.out.printf("\nAfter %3d  root: %.10f ",iteration,root2);
                return false;
            }

            iteration ++;
            System.out.printf("%3d              %.10f       %.10f\n",iteration,absoluteError(root1,root2),relativeError(root1,root2));
            root1 = root2;

        }
        System.out.println("Cannot find root on bisection method.\n");

        return false;
    }

    /**
     * Change function F for a new problem
     * @param target parameter of funciton
     * @return double
     */
    private static double function(double target)
    {
        double value ;
        //value = (3 * target) -(Math.exp(target)) ; // 6.A 1 <= x<= 2
        //value = (2 * target) + 3 * Math.cos(target) - Math.exp(target); // 6.B 0 ≤ x ≤ 1
        //value = (target * target) - 4 * target + 4 - Math.log(target); // 6.C ln all
        value = (target + 1) - (2 * Math.sin(Math.PI*target));
        return value;
    }

    private static boolean errorChecks(String errorType, double root1, double root2, double epsilon)
    {
        if("DISTANCE_TO_ROOT".equals(errorType))
        {
            if(Math.abs(function(root1)) < epsilon)
                return true;
            else
                return false;
        }
        if("ABSOLUTE_ERROR".equals(errorType))
        {
            if(Math.abs(root1 - root2) < epsilon)
                return true;
            else
                return false;
        }
        if("RELATIVE_ERROR".equals(errorType))
        {
            if(Math.abs(root1 - root2) / Math.abs(root2) < epsilon)
                return true;
            else
                return false;
        }

        return false;
    }

    private static double relativeError(double root1, double root2)
    {
        return Math.abs(root1 - root2) / Math.abs(root2);
    }

    private static double absoluteError(double root1, double root2)
    {
        return Math.abs(root1 - root2);
    }

    private static double distanceToRoot(double root1, double root2)
    {
        return Math.abs(function(root1));
    }
}