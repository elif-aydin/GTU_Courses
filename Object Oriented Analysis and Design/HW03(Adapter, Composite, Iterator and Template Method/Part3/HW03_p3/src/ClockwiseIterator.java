import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * An Iterator implementation for clockwise printing.
 */
public class ClockwiseIterator implements Iterator
{
    private Iterator ite = null;

    /**
     * Constructor to configure inner iterator.
     * @param data data to iterate
     */
    public ClockwiseIterator(int[][] data)
    {
        if (data.length == 0 || data[0].length == 0)
            return;

        int pos = 1;
        int yStart = 0;
        int yEnd = data.length - 1;
        int xStart = 0;
        int xEnd = data[0].length - 1; // matrix should be square

        List<Integer> list = new ArrayList<>();
        while (xStart <= xEnd && yStart <= yEnd)  // continue until we reach any border
        {
            if (pos == 1)   // go from left to right
            {
                for (int i = xStart; i <= xEnd; ++i)
                    list.add(data[yStart][i]);
                ++yStart;
                pos = 2;    // turn down
            }
            else if (pos == 2)
            {
                for (int i = yStart; i <= yEnd; ++i) // go from up to down
                    list.add(data[i][xEnd]);
                --xEnd;
                pos = 3;    // turn left
            }
            else if (pos == 3)
            {
                for (int i = xEnd; i >= xStart; --i) // go from right to left
                    list.add(data[yEnd][i]);
                --yEnd;
                pos = 4;    // turn up
            }
            else
            {
                for (int i = yEnd; i >= yStart; --i) // go from down to up
                    list.add(data[i][xStart]);
                ++xStart;
                pos = 1;    // turn right
            }
        }
        ite = list.iterator();
    }

    /**
     * It checks the iteration value has next value or not.
     * @return status of this checking
     */
    @Override
    public boolean hasNext()
    {
        return ite.hasNext();
    }

    /**
     * Get next from pre-calculated data.
     * @return next value
     */
    @Override
    public Object next()
    {
        return ite.next();
    }
}
