import java.util.Map;

public class MyEntry<K extends Comparable<K>, V extends Comparable<V>> implements Comparable<MyEntry<K, V>>, Map.Entry<K, V> {

    private K key;
    private V value;

    /**
     * Constructor...
     * @param key key of pair
     * @param value value of pair
     */
    MyEntry(K key, V value)
    {
        this.key = key;
        this.value = value;
    }

    /**
     * Gets key
     * @return key
     */
    @Override
    public K getKey()
    {
        return key;
    }

    /**
     * Gets value.
     * @return value
     */
    @Override
    public V getValue()
    {
        return value;
    }

    /**
     * Sets the value of this pair.
     * @param value value to set
     * @return old value
     */
    @Override
    public V setValue(V value) {
        V old = this.value;
        this.value = value;
        return old;
    }

    /**
     * Realization of Comparable interface.
     * @param o Object to compare
     * @return compareTo result of keys.
     */
    @Override
    public int compareTo(MyEntry<K, V> o)
    {
        return key.compareTo((K) o.getKey());
    }

    /**
     * String representation of the pair.
     * @return string value
     */
    @Override
    public String toString()
    {
        return key.toString() + "=" + value.toString();
    }
}
