import java.util.AbstractCollection;
import java.util.Collection;
import java.util.Iterator;

/**
 * Created by elif on 13-Mar-17.
 */
public abstract class MyAbstractCollection<E> extends AbstractCollection<E>
{
    /**
     * This method appends any AbstractCollection object to any other
     * @param other Object to any other AbstractCollection object by concatenating them.
     */
    public void appendAnything(MyAbstractCollection<E> other)
    {
        Iterator<E> iter;
        iter = other.iterator();

        while(iter.hasNext())
            this.add(iter.next());
    }
}
