import java.util.NoSuchElementException;

/**
 * Created by elif on 21-Mar-17.
 */
public interface StackInterface<T>
{
    /** This method pushes an item onto the top of the stack and returns
     *the item pushed.
     *@return The object inserted
     * @param obj The object to be inserted
     */
    T push(T obj);

    /** This method Returns the object at the top of the stack
     *and removes it.
     *@return The object at the top of the stack
     *@throws NoSuchElementException if stack is empty
     */
    T pop();

    /** This method returns true if the stack is empty; otherwise,
     *returns false.
     *@return true (false) if the stack is empty (not empty)
     */
    boolean isEmpty();

    /** This method returns the stack size
     * @return The stack size
     */
    int size();
}
