import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * This is a implementation of Java's StringBuilder method
 * @author elif
 */
public class MyStringBuilder
{
    public SingleLinkedList<Object> singleLinkedList = new SingleLinkedList<>();

    /**
     * This function append given object to list.
     * @param obj Object for append
     * @throws NoSuchElementException If given object is null
     */
    public void append(Object obj) throws NoSuchElementException
    {
        if(obj==null)
        {
            throw new NoSuchElementException();
        }
        singleLinkedList.add(obj);
    }

    /**
     * Implementation of toString method with indexes
     * @return String from returned toString
     */
    public String toStringWithIndexes()
    {
        String toBeReturned = "";

        for(int i = 0; i < singleLinkedList.size(); i++)
            toBeReturned += singleLinkedList.get(i) + "\n";

        return toBeReturned;
    }

    /**
     * Implementation of toString method with iterator
     * @return String from returned toString
     */
    public String toStringWithIterator()
     {
        String toBeReturned = "";
        Iterator iter = singleLinkedList.iterator();

        while (iter.hasNext())
            toBeReturned += iter.next().toString() + "\n";

        return toBeReturned;
    }

    /**
     * Implementation of toString method
     * @return String
     */
    public String toString()
    {
        return singleLinkedList.toString();
    }
}
