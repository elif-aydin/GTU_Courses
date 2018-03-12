import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;


/**
 * Created by elif on 18-Apr-17.
 */
public class MainQ1
{
    public static void main(String[] args) throws Exception
    {
        BinaryHeap<Passenger> binaryHeap = new BinaryHeap<Passenger>();

        BufferedReader br = new BufferedReader(new FileReader(new File("passengers.txt")));
        String line;
        while ((line = br.readLine()) != null)
        {
            String[] tokens = line.split(" ");
            Passenger passenger = new Passenger(tokens[0], 1.0/(Double.parseDouble(tokens[1])));
            binaryHeap.offer(passenger);
        }

        br.close();
        int size = binaryHeap.size();
        for(int i = 0; i < size; i++)
        {
            Passenger passenger = binaryHeap.poll();
            System.out.println(passenger);
        }
    }

    static class Passenger implements Comparable
    {
            String name;
            Double priority;

            public Passenger(String name, Double p)
            {
                this.name = name;
                this.priority = p;
            }

            /**
             * Compares this object with the specified object for order.  Returns a
             * negative integer, zero, or a positive integer as this object is less
             * than, equal to, or greater than the specified object.
             * @param o the object to be compared.
             * @return a negative integer, zero, or a positive integer as this object
             * is less than, equal to, or greater than the specified object.
             * @throws NullPointerException if the specified object is null
             * @throws ClassCastException   if the specifct's type prevents it
             *                              from being compared to this object.ied obje
             */
            @Override
            public int compareTo(Object o)
            {
                Passenger other = (Passenger) o;
                return this.priority.compareTo(other.priority);
            }

            public String toString()
            {
                return name;
            }

        /**
         * This method indicates whether some other object is "equal to" this one.
         * @param obj - the reference object with which to compare.
         * @return true if this object is the same as the obj argument; false otherwise.
         */
            @Override
            public boolean equals(Object obj)
            {
                Passenger other = (Passenger) obj;
                return this.priority == other.priority;
            }
        }
}
