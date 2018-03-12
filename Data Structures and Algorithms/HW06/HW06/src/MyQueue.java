import java.util.NoSuchElementException;

/**
 * Created by elif on 22-Mar-17.
 */

public interface MyQueue<E>
{
    /**
     * Inserts the specified element into this queue
     * @param data  the element to add
     * @return true if the element was added to this queue, else false
     */
    public boolean offer(E data);

    public int size();

    /**
     * Retrieves and removes the head of this queue, or returns null if this queue is empty
     * @return the head of this queue, or null if this queue is empty
     * @throws NoSuchElementException if the queue is empty
     */
    public E poll() throws NoSuchElementException;

    /**
     * Retrieves, but does not remove, the head of this queue, or returns null if this queue is empty
     * @return the head of this queue, or null if this queue is empty
     * @throws NoSuchElementException if the queue is empty
     */
    public E peek() throws NoSuchElementException;


    /**
     * Returns a string representation of this collection
     * @return a string representation of this collection
     */
    public String toString();
}
