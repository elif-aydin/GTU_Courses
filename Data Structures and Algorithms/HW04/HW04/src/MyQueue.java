import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Created by elif on 22-Mar-17.
 */

public class MyQueue<E> extends KWLinkedList<E>
{

    /**
     * Reverses the queue
     */
    public void reverse()
    {
        if(this.isEmpty())
        return;

        int tempSize = size()-1;

        for (int i = tempSize; i >= 0; i--)
        {
            this.offer(this.get(i));

        }
        for (int i = 0; i < tempSize + 1; i++)
        {
            this.poll();

        }
    }

    /**
     * Inserts the specified element into this queue
     * @param data  the element to add
     * @return true if the element was added to this queue, else false
     */
    public boolean offer(E data)
    {
        this.addLast(data);
        return true;
    }

    /**
     * Retrieves and removes the head of this queue, or returns null if this queue is empty
     * @return the head of this queue, or null if this queue is empty
     * @throws NoSuchElementException if the queue is empty
     */
    public E poll() throws NoSuchElementException
    {
        if(this.isEmpty())
            throw new NoSuchElementException();

        else
        {
            Iterator<E> iterator = this.iterator();
            E temp = iterator.next();
            iterator.remove();
            return temp;
        }
    }

    /**
     * Retrieves, but does not remove, the head of this queue, or returns null if this queue is empty
     * @return the head of this queue, or null if this queue is empty
     * @throws NoSuchElementException if the queue is empty
     */
    public E peek() throws NoSuchElementException
    {
        if(this.isEmpty())
            throw new NoSuchElementException();

        else
        {
            Iterator<E> iterator = this.iterator();
            E temp = iterator.next();
            return temp;
        }
    }

    /**
     * Returns a string representation of this collection
     * @return a string representation of this collection
     */
    public String toString()
    {
        String temp = "";

        for (int i = 0; i < this.size() ; i++)
        {
            temp += (this.get(i) + ",");
        }

        return temp.substring(0, temp.length()-1);
    }
}
