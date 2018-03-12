import java.util.LinkedList;
import java.util.NoSuchElementException;

/**
 * Created by elif on 23-Mar-17.
 */
public class PriorityQueueB<E extends Comparable<E>>
{
    LinkedList<E> linkedList = new LinkedList<E>();

    /**
     * Inserts the specified element into priority queue.
     * @param data The element to add
     * @return The element to add
     */
    public E insert(E data)
    {
        linkedList.add(data);
        sortQueue();
        return data;
    }

    /**
     * Deletes and returns the highest priority  element
     * @return highest priority element
     * @throws NoSuchElementException exception
     */
    public E deleteMin() throws NoSuchElementException
    {
        if(isEmpty())
            throw new NoSuchElementException();

        E temp = linkedList.get(0);
        linkedList.remove();
        return temp;
    }

    /**
     * This function sorts the queue
     */
    private void sortQueue()
    {
        E temp;
        for (int i = 1; i < this.size(); i++)
            for(int j = i ; j > 0 ; j--)
                if(linkedList.get(j).compareTo(linkedList.get(j-1)) < 0)
                {
                    temp = linkedList.get(j);
                    linkedList.set(j, linkedList.get(j-1));
                    linkedList.set(j-1, temp);
                }
    }

    /**
     * Returns true if this collection contains no elements.
     * @return true if this collection contains no elements
     */
    public boolean isEmpty()
    {
        return size() == 0;
    }

    /**
     * Returns the number of elements in this collection
     * @return the number of elements in this collection
     */
    public int size()
    {
        return linkedList.size();
    }

    /**
     * Returns a string representation of this collection
     * @return a string representation of this collection
     */
    public String toString()
    {
        String temp = "";

        for (int i = 0; i < linkedList.size() ; i++)
        {
            temp += (linkedList.get(i) + ",");
        }

        return temp.substring(0, temp.length()-1);

    }

}
