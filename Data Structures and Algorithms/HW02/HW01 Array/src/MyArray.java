/**
 * Created by elif on 03-Mar-17.
 */

import java.util.NoSuchElementException;
public class MyArray
{
    private Object[] data;
    private int size ;
    private int capacity = 10;

    public MyArray()
    {
        size = 0;
        data = new Object[capacity]; // Initial value for array
    }

    public Object get(int index)
    {
        if(index < 0 || index >= size)
            throw new ArrayIndexOutOfBoundsException(index);

        return data[index];
    }


    public Object set(int index, Object obj) throws Exception
    {
        if(index < 0 || index >= size)
            throw new ArrayIndexOutOfBoundsException(index);

        Object newObj = data[index];
        data[index] = obj;

        return newObj;
    }

    public void remove(Object obj)
    {
        int index = -1;
        for (int i = 0; i < size ; i++)
        {
            if(data[i].getClass() == obj.getClass())
            {
                if (data[i].equals(obj))
                {
                    index = i;
                }
            }
        }
        if(index == -1) // Bulamadiysa
            throw new NoSuchElementException();

        for (int i = index; i < size -1; i++)
        {
             data[index] = data[index+1];
        }
        size --;

    }

    public boolean add(Object obj)
    {
        if(size == capacity)
        {
            reallocate();
        }

        data[size] = obj;
        size ++;
        return true;
    }

    private void reallocate()
    {
        int old = capacity;
        Object [] tempArray = new Object [old];
        for (int i = 0; i < old; i++)
        {
            tempArray[i] = data[i];
        }

        capacity *= 2;
        data = new Object [capacity];

        for (int i = 0; i < old ; i++)
        {
            data[i] = tempArray [i];
        }

    }


    public int size()
    {
        return size;
    }
}
