import java.util.Iterator;

/**
 * Created by elif on 14-Mar-17.
 */
public class MainQ2
{
    public static void main(String[] args)
    {
        SingleLinkedList<Character> list = new SingleLinkedList<>();

        list.add('a');
        list.add('b');
        list.add('c');
        list.add('d');
        list.add('e');

        System.out.println("Printing list to the screen...");
        Iterator iter = list.iterator();
        while (iter.hasNext())
            System.out.println(iter.next());

        System.out.println("\nStraight recursive : " + list.recursiveToString());
        System.out.println("Reverse recursive : " + list.reverseToString());
    }
}
