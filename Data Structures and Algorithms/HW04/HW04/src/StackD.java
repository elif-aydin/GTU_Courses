import java.util.EmptyStackException;
import java.util.LinkedList;
import java.util.Queue;
import java.util.ArrayDeque;

/**
 * Created by elif on 21-Mar-17.
 */
public class StackD<T> implements StackInterface<T>
{
    // Data fields
    private Queue<T> queue;
    private int size = 0;

    public StackD()
    {
        this.queue = new LinkedList<T>();
    }

    /**
     * This method pushes an item onto the top of the stack and returns
     * the item pushed.
     * @param obj The object to be inserted
     * @return The object inserted
     */
    @Override
    public T push(T obj)
    {
        queue.offer(obj);
        size ++;
        return obj;
    }

    /**
     * This method Returns the object at the top of the stack
     * and removes it.
     * @return The object at the top of the stack
     * @throws EmptyStackException if stack is empty
     */
    @Override
    public T pop()
    {
        int temp = 0;
        T thing;

        if (isEmpty())
            throw new EmptyStackException();

        while (temp < size-1)
        {
            thing = queue.poll();
            queue.offer(thing);
            temp ++;
        }

        size --;
        return (queue.poll());
    }

    /**
     * This method returns true if the stack is empty; otherwise,
     * returns false.
     * @return true (false) if the stack is empty (not empty)
     */
    @Override
    public boolean isEmpty()
    {
        return queue.size() == 0;
    }

    /**
     * This method returns the stack size
     * @return The stack size
     */
    @Override
    public int size()
    {
        return size;
    }

    /**
     * Returns a string representation of this collection
     * @return a string representation of this collection
     */
    @Override
    public String toString()
    {
        String temp = "";
        String str = queue.toString().replace("[", "").replace("]", "").replaceAll(" ", "");

        String[] arr = str.split(",");

        for (int i = arr.length-1; i >= 0; --i) {
            temp += (arr[i] + ",");
        }

        return temp.substring(0, temp.length()-1);
    }
}
