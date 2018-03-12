import java.util.*;

/**
 * Created by syucer on 4/24/2017.
 */
public class HashTableChaining<K extends Comparable <K>, V  extends Comparable <V>> implements HashMap<K, V> {

    private static final int INIT_CAP = 10;
    private static final double loadFactor = 0.75;
    private List<HashTable<K, V>> tables;
    private int size;
    private int capacity;

    /**
     * Initialize with given capacity.
     * @param cap capacity
     */
    public HashTableChaining(int cap)
    {
        capacity = cap;
        if (capacity < INIT_CAP)
            capacity = INIT_CAP;

        tables = new ArrayList<>(capacity);
        for (int i = 0; i < capacity; ++i)
            tables.add(null);
        size = 0;
    }

    /**
     * No parameter const.
     */
    public HashTableChaining()
    {
        this(INIT_CAP);
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
     * Resize the table.
     * @param newCap new capacity of the table.
     */
    private void resize(int newCap)
    {
        HashTableChaining<K, V> newMap = new HashTableChaining<>(newCap);
        for (int i = 0; i < capacity; i++) {
            HashTable<K, V> curTable = tables.get(i);
            if (curTable != null)
                for (Map.Entry<K, V> e : curTable.entrySet())
                    newMap.put(e.getKey(), e.getValue());
        }
        tables = newMap.tables;
        capacity = newCap;
    }

    /**
     * Finds the first value that the key matches (the first added value).
     * @param key key to search
     * @return value that pairs with key.
     */
    @Override
    public V get(Object key)
    {
        int tableIndex = getHashIndex(key);
        if (tables.get(tableIndex) == null)
            return null;

        return tables.get(tableIndex).get(key);
    }

    /**
     * Adds the given key-value pair to the map.
     * @param key key of pair
     * @param value value of pair
     * @return value
     */
    @Override
    public V put(K key, V value)
    {
        if (key == null || value == null)
        {
            throw new UnsupportedOperationException("key and/or value is null");
        }

        if (size >= capacity * loadFactor)
        {
            resize(2 * capacity);
        }

        int tableIndex = getHashIndex(key);
        if (tables.get(tableIndex) == null)
        {
            tables.set(tableIndex, new HashTable<>());
        }

        ++size;
        return tables.get(tableIndex).put(key, value);
    }

    /**
     * Removes the first value that the key matches (the first added value).
     * @param key key to search
     * @return value that pairs with key.
     */
    @Override
    public V remove(Object key)
    {
        int tableIndex = getHashIndex(key);
        if (tables.get(tableIndex) == null)
            return null;

        V ret = tables.get(tableIndex).remove(key);
        if (ret != null)
            size--;

        return ret;
    }

    /**
     * Gets all pairs of this map as an entry set.
     * @return Set version of pairs of this map.
     */
    public Set<Map.Entry<K, V>> entrySet()
    {
        Set<Map.Entry<K, V>> set = new HashSet<>();
        for (int i = 0; i < capacity; i++) {
            HashTable<K, V> table = tables.get(i);
            if (table != null)
                set.addAll(table.entrySet());
        }

        return set;
    }

    /**
     * Size.
     * @return Number of elements in the map.
     */
    @Override
    public int size()
    {
        return size;
    }

    /**
     * Check if map is empty or not.
     * @return true if empty, false if non-empty
     */
    @Override
    public boolean isEmpty()
    {
        return size == 0;
    }

    /**
     * String version of map. the empty slots shown as null.
     * @return String version of map.
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("All\n\n");
        for (int i = 0; i < capacity; i++)
        {
            if (tables.get(i) == null)
                sb.append("null HashTable\n\n");
            else
                sb.append(tables.get(i)).append("\n");
        }

        return sb.append("\n").toString();
    }

    /**
     * Converts the entrySet to string representation. No null strings like in the toString method.
     * @return string representation of the map.
     */
    public String getElementsAsString()
    {
        Set<Map.Entry<K, V>> entries = entrySet();
        List<String> resultStrings = new ArrayList<>();
        for (Map.Entry<K, V> e : entries)
            resultStrings.add(e.toString());

        Collections.sort(resultStrings);
        int i = 1;
        StringBuilder sb = new StringBuilder(String.format("Size: %d\n", size));
        for (String s : resultStrings)
            sb.append(String.format("%3d -> %s\n", (i++), s));

        return sb.append("\n").toString();
    }
}
