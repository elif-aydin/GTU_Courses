/**
 * Created by elif on 14-Mar-17.
 */
public class MainQ4 {

    public static void main(String[] args) {

        SingleLinkedList<Integer> list = new SingleLinkedList<>();

        for (int i = 0; i < 100; i++)
        {
            list.add(i);
        }

        for (int i = 99; i > 49; i--)
        {
            list.remove(i);
            //System.out.println("removed. size: " + list.size());
        }

        System.out.println("Deleted element list after removing last 50 elements from list: ");
        System.out.println(list.deletedToString());

        for (int i = 0; i < 100; i++)
        {
            list.add(i);
        }

        System.out.println("Deleted element list after adding 100 more elements: ");
        System.out.println(list.deletedToString());
    }
}
