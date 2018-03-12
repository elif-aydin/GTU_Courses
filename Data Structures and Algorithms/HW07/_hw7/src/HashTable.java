import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class HashTable<K extends Comparable <K>, V  extends Comparable <V>>
{

    private static final int INIT_CAP = 10;
    private static final double loadFactor = 0.75;
    private MyEntry<K, V>[] table;
    private int size;
    private int capacity;

    /**
     * Initialize with given capacity.
     * @param cap capacity
     */
    public HashTable(int cap)
    {
        capacity = cap;
        if (capacity < INIT_CAP)
            capacity = INIT_CAP;

        table = new MyEntry[capacity];
        size = 0;
    }

    /**
     * No parameter const.
     */
    public HashTable()
    {
        this(INIT_CAP);
    }

    /**
     * Resize the table.
     * @param newCap new capacity of the table.
     */
    private void resize(int newCap)
    {
        HashTable<K, V> newMap = new HashTable<>(newCap);
        for (int i = 0; i < capacity; i++) {
            MyEntry<K, V> curEntry = table[i];
            if (curEntry != null && curEntry.getKey() != null)
                newMap.put(curEntry.getKey(), curEntry.getValue());
        }
        table = newMap.table;
        capacity = newCap;
    }

    /**
     * Calculates the index of this key in the array.
     * @param key key to calculate
     * @return the index value
     */
    private int getHashIndex(Object key)
    {
        int res = key.hashCode() % capacity;
        return res < 0 ? (res + capacity) : res;
    }

    /**
     * Adds the given key-value pair to the map.
     * @param key key of pair
     * @param value value of pair
     * @return value
     */
    public V put(K key, V value)
    {
        if (key == null)
            return null;
        if (value == null)
            throw new UnsupportedOperationException("Key and Value must not equals null");
        if (size >= capacity * loadFactor)
        {
            resize(2 * capacity);
        }

        int i;
        MyEntry<K, V> curEntry;
        for (i = getHashIndex(key); table[i] != null; i = (i + 1) % capacity) {
//            curEntry = table[i];
//            if (curEntry.equals(key))
//            {
//                curEntry.setValue(value);
//                return value;
//            }
        }
        table[i] = new MyEntry<>(key, value);
        size++;
        return (V) table[i].getValue();
    }

    /**
     * Finds the first value that the key matches (the first added value).
     * @param key key to search
     * @return value that pairs with key.
     */
    public V get(Object key)
    {
        if (size == 0)
            return null;
        MyEntry<K, V> curEntry;
        for (int i = getHashIndex(key); table[i] != null; i = (i+1) % capacity)
        {
            curEntry = table[i];
            if (curEntry.getKey().equals(key))
                return curEntry.getValue();
        }
        return null;
    }

    /**
     * Removes the first value that the key matches (the first added value).
     * @param key key to search
     * @return value that pairs with key.
     */
    public V remove(Object key)
    {
        if (get(key) == null)
            return null;

        int i = getHashIndex(key);
        while (!key.equals(table[i].getKey()) )
            i = (i + 1) % capacity;

        V retValue = table[i].getValue();
        table[i] = null;

        i = (i + 1) % capacity;
        MyEntry<K, V> curEntry;
        while (table[i] != null)
        {
            curEntry = table[i];
            table[i] = null;
            size--;
            put(curEntry.getKey(), curEntry.getValue());
            i = (i + 1) % capacity;
        }
        size--;
        return retValue;
    }

    /**
     * Gets all pairs of this map as an entry set.
     * @return Set version of pairs of this map.
     */
    public Set<Map.Entry<K, V>> entrySet()
    {
        Set<Map.Entry<K, V>> set = new HashSet<>();
        for (int i = 0; i < capacity; i++) {
            MyEntry<K, V> temp = table[i];
            if (temp != null)
                set.add(temp);
        }

        return set;
    }

    /**
     * String version of map. the empty slots shown as null.
     * @return String version of map.
     */
    @Override
    public String toString()
    {
        StringBuilder sb = new StringBuilder("HashTable\n");
        for (int i = 0; i < capacity; i++)
        {
            if (table[i] == null)
                sb.append("null Entry\n");
            else
                sb.append(table[i]).append("\n");
        }

        return sb.append("\n").toString();
    }
}
