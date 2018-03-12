import java.util.LinkedList;
import java.util.NoSuchElementException;

/**
 * Created by elif on 23-Mar-17.
 */
public class PriorityQueueA<E extends Comparable<E>> extends LinkedList<E>
{

    /**
     * Inserts the specified element into priority queue.
     * @param data The element to add
     * @return The element to add
     */
    public E insert(E data)
    {
        this.add(data);
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
        if (isEmpty())
            throw new NoSuchElementException();
        E temp = this.get(0);
        super.remove(0);
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
                if(this.get(j).compareTo(this.get(j-1)) < 0)
                {
                    temp = this.get(j);
                    this.set(j, this.get(j-1));
                    this.set(j-1, temp);
                }
    }

    /**
     * Returns a string representation of this collection
     * @return a string representation of this collection
     */
    public String toString()
    {
        String temp = "";

        for (int i = 0; i < super.size() ; i++)
        {
            temp += (super.get(i) + ",");
        }

        return temp.substring(0, temp.length()-1);

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
        return super.size();
    }

}
