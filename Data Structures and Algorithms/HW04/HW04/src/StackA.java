import java.util.ArrayList;
import java.util.EmptyStackException;

/**
 * Created by elif on 21-Mar-17.
 */
public class StackA<E> extends ArrayList<E> implements StackInterface<E>
{

    /** This method pushes an item onto the top of the stack and returns
     *the item pushed.
     *@return The object inserted
     * @param obj The object to be inserted
     */
    @Override
    public E push (E obj)
    {
        add(obj);
        return obj;
    }

    /** This method returns the object at the top of the stack
     *and removes it.
     *@return The object at the top of the stack
     *@throws EmptyStackException if stack is empty
     */
    @Override
    public E pop() throws EmptyStackException
    {
        if(isEmpty())
            throw new EmptyStackException();

        E temp = this.get(size() -1);
        remove(size() - 1);
        return temp;
    }

    /** This method returns true if the stack is empty; otherwise,
     *returns false.
     *@return true (false) if the stack is empty (not empty)
     */
    @Override
    public boolean isEmpty()
    {
        return size() == 0;
    }

    /** This method returns the stack size
     * @return The stack size
     */
    @Override
    public int size()
    {
        return super.size();
    }

    /**
     * Returns a string representation of this collection.
     * @return a string representation of this collection
     */
    @Override
    public String toString()
    {
        String temp = "";

        for (int i = this.size()-1; i >= 0; i--)
        {
            temp += this.get(i) + ",";
        }

        return temp.substring(0, temp.length()-1);
    }
}
