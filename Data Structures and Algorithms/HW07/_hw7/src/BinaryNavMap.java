/**
 * Created by syucer on 4/24/2017.
 */
import java.util.*;

public class BinaryNavMap<K extends Comparable <K>, V  extends Comparable <V>> extends AbstractMap<K,V>
        implements NavigableMap<K,V>, Cloneable, java.io.Serializable
{

    private BinarySearchTree<MyEntry<K, V>> bst = new BinarySearchTree();

    /**
     * Adds the given key-value pair to the map. Swaps the values if the key is exist.
     * @param key key of pair
     * @param value value of pair
     * @return value
     */
    @Override
    public V put(K key, V value)
    {
        MyEntry<K, V> e = new MyEntry<>(key, value);
        MyEntry<K, V> res = bst.find(e);
        if (res == null)
        {
            bst.add(e);
        }

        else
        {
            bst.delete(e);
            bst.add(e);
        }
        return value;
    }

    /**
     * Gets all pairs of this map as an entry set.
     * @return Set version of pairs of this map.
     */
    @Override
    public Set<Entry<K, V>> entrySet()
    {
        Set<Entry<K, V>> result = new HashSet<>();
        Iterator it = bst.iterator();
        while (it.hasNext())
        {
            result.add((Entry<K, V>) it.next());
        }
        return result;
    }

    /**
     * Returns a key-value mapping associated with the greatest key
     * strictly less than the given key, or {@code null} if there is
     * no such key.
     *
     * @param key the key
     * @return an entry with the greatest key less than {@code key},
     * or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public Entry<K, V> lowerEntry(K key)
    {
        Iterator it = bst.iterator();
        Entry<K, V> res = null;

        while (it.hasNext()) {
            Entry<K, V> n = (Entry<K, V>) it.next();
            K n_key = n.getKey();
            if (n_key.compareTo(key) < 0 && (res == null || n_key.compareTo(res.getKey()) > 0))
                res = n;
        }

        return res;
    }

    /**
     * Returns the greatest key strictly less than the given key, or
     * {@code null} if there is no such key.
     *
     * @param key the key
     * @return the greatest key less than {@code key},
     * or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public K lowerKey(K key)
    {
        Iterator it = bst.iterator();
        K res = null;

        while (it.hasNext()) {
            Entry<K, V> n = (Entry<K, V>) it.next();
            K n_key = n.getKey();
            if (n_key.compareTo(key) < 0 && (res == null || n_key.compareTo(res) > 0))
                res = n_key;
        }

        return res;
    }

    /**
     * Returns a key-value mapping associated with the greatest key
     * less than or equal to the given key, or {@code null} if there
     * is no such key.
     *
     * @param key the key
     * @return an entry with the greatest key less than or equal to
     * {@code key}, or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public Entry<K, V> floorEntry(K key)
    {
        Iterator it = bst.iterator();
        Entry<K, V> res = null;

        while (it.hasNext()) {
            Entry<K, V> n = (Entry<K, V>) it.next();
            K n_key = n.getKey();
            if (n_key.compareTo(key) <= 0 && (res == null || n_key.compareTo(res.getKey()) > 0))
                res = n;
        }

        return res;
    }

    /**
     * Returns the greatest key less than or equal to the given key,
     * or {@code null} if there is no such key.
     *
     * @param key the key
     * @return the greatest key less than or equal to {@code key},
     * or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public K floorKey(K key)
    {
        Iterator it = bst.iterator();
        K res = null;

        while (it.hasNext()) {
            Entry<K, V> n = (Entry<K, V>) it.next();
            K n_key = n.getKey();
            if (n_key.compareTo(key) <= 0 && (res == null || n_key.compareTo(res) > 0))
                res = n_key;
        }

        return res;
    }

    /**
     * Returns a key-value mapping associated with the least key
     * greater than or equal to the given key, or {@code null} if
     * there is no such key.
     *
     * @param key the key
     * @return an entry with the least key greater than or equal to
     * {@code key}, or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public Entry<K, V> ceilingEntry(K key)
    {
        Iterator it = bst.iterator();
        Entry<K, V> res = null;

        while (it.hasNext()) {
            Entry<K, V> n = (Entry<K, V>) it.next();
            K n_key = n.getKey();
            if (n_key.compareTo(key) >= 0 && (res == null || n_key.compareTo(res.getKey()) < 0))
                res = n;
        }

        return res;
    }

    /**
     * Returns the least key greater than or equal to the given key,
     * or {@code null} if there is no such key.
     *
     * @param key the key
     * @return the least key greater than or equal to {@code key},
     * or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public K ceilingKey(K key)
    {
        Iterator it = bst.iterator();
        K res = null;

        while (it.hasNext())
        {
            Entry<K, V> n = (Entry<K, V>) it.next();
            K n_key = n.getKey();
            if (n_key.compareTo(key) >= 0 && (res == null || n_key.compareTo(res) < 0))
                res = n_key;
        }

        return res;
    }

    /**
     * Returns a key-value mapping associated with the least key
     * strictly greater than the given key, or {@code null} if there
     * is no such key.
     *
     * @param key the key
     * @return an entry with the least key greater than {@code key},
     * or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public Entry<K, V> higherEntry(K key)
    {
        Iterator it = bst.iterator();
        Entry<K, V> res = null;

        while (it.hasNext())
        {
            Entry<K, V> n = (Entry<K, V>) it.next();
            K n_key = n.getKey();
            if (n_key.compareTo(key) > 0 && (res == null || n_key.compareTo(res.getKey()) < 0))
                res = n;
        }

        return res;
    }

    /**
     * Returns the least key strictly greater than the given key, or
     * {@code null} if there is no such key.
     *
     * @param key the key
     * @return the least key greater than {@code key},
     * or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public K higherKey(K key)
    {
        Iterator it = bst.iterator();
        K res = null;

        while (it.hasNext())
        {
            Entry<K, V> n = (Entry<K, V>) it.next();
            K n_key = n.getKey();
            if (n_key.compareTo(key) > 0 && (res == null || n_key.compareTo(res) < 0))
                res = n_key;
        }

        return res;
    }

    /**
     * Returns a key-value mapping associated with the least
     * key in this map, or {@code null} if the map is empty.
     *
     * @return an entry with the least key,
     * or {@code null} if this map is empty
     */
    @Override
    public Entry<K, V> firstEntry()
    {
        Iterator it = bst.iterator();
        Entry<K, V> res = null;

        while (it.hasNext())
        {
            Entry<K, V> n = (Entry<K, V>) it.next();
            K n_key = n.getKey();
            if (res == null || n_key.compareTo(res.getKey()) < 0)
                res = n;
        }

        return res;
    }

    /**
     * Returns a key-value mapping associated with the greatest
     * key in this map, or {@code null} if the map is empty.
     *
     * @return an entry with the greatest key,
     * or {@code null} if this map is empty
     */
    @Override
    public Entry<K, V> lastEntry()
    {
        Iterator it = bst.iterator();
        Entry<K, V> res = null;

        while (it.hasNext())
        {
            Entry<K, V> n = (Entry<K, V>) it.next();
            K n_key = n.getKey();
            if (res == null || n_key.compareTo(res.getKey()) > 0)
                res = n;
        }

        return res;
    }

    /**
     * Removes and returns a key-value mapping associated with
     * the least key in this map, or {@code null} if the map is empty.
     *
     * @return the removed first entry of this map,
     * or {@code null} if this map is empty
     */
    @Override
    public Entry<K, V> pollFirstEntry()
    {
        Iterator it = bst.iterator();
        if (!it.hasNext())
            return null;
        MyEntry<K, V> first = (MyEntry<K, V>) firstEntry();
        bst.remove(first);

        return first;
    }

    /**
     * Removes and returns a key-value mapping associated with
     * the greatest key in this map, or {@code null} if the map is empty.
     *
     * @return the removed last entry of this map,
     * or {@code null} if this map is empty
     */
    @Override
    public Entry<K, V> pollLastEntry()
    {
        Iterator it = bst.iterator();
        if (!it.hasNext())
            return null;
        MyEntry<K, V> last = (MyEntry<K, V>) lastEntry();
        bst.remove(last);

        return last;
    }

    /**
     * Returns a reverse order view of the mappings contained in this map.
     * The descending map is backed by this map, so changes to the map are
     * reflected in the descending map, and vice-versa.  If either map is
     * modified while an iteration over a collection view of either map
     * is in progress (except through the iterator's own {@code remove}
     * operation), the results of the iteration are undefined.
     * <p>
     * <p>The returned map has an ordering equivalent to
     * <tt>{@link Collections#reverseOrder(Comparator) Collections.reverseOrder}(comparator())</tt>.
     * The expression {@code m.descendingMap().descendingMap()} returns a
     * view of {@code m} essentially equivalent to {@code m}.
     *
     * @return a reverse order view of this map
     */
    @Override
    public NavigableMap<K, V> descendingMap()
    {
        return null;
    }

    /**
     * Returns a {@link NavigableSet} view of the keys contained in this map.
     * The set's iterator returns the keys in ascending order.
     * The set is backed by the map, so changes to the map are reflected in
     * the set, and vice-versa.  If the map is modified while an iteration
     * over the set is in progress (except through the iterator's own {@code
     * remove} operation), the results of the iteration are undefined.  The
     * set supports element removal, which removes the corresponding mapping
     * from the map, via the {@code Iterator.remove}, {@code Set.remove},
     * {@code removeAll}, {@code retainAll}, and {@code clear} operations.
     * It does not support the {@code add} or {@code addAll} operations.
     *
     * @return a navigable set view of the keys in this map
     */
    @Override
    public NavigableSet<K> navigableKeySet()
    {
        return null;
    }

    /**
     * Returns a reverse order {@link NavigableSet} view of the keys contained in this map.
     * The set's iterator returns the keys in descending order.
     * The set is backed by the map, so changes to the map are reflected in
     * the set, and vice-versa.  If the map is modified while an iteration
     * over the set is in progress (except through the iterator's own {@code
     * remove} operation), the results of the iteration are undefined.  The
     * set supports element removal, which removes the corresponding mapping
     * from the map, via the {@code Iterator.remove}, {@code Set.remove},
     * {@code removeAll}, {@code retainAll}, and {@code clear} operations.
     * It does not support the {@code add} or {@code addAll} operations.
     *
     * @return a reverse order navigable set view of the keys in this map
     */
    @Override
    public NavigableSet<K> descendingKeySet()
    {
        return null;
    }

    /**
     * Returns a view of the portion of this map whose keys range from
     * {@code fromKey} to {@code toKey}.  If {@code fromKey} and
     * {@code toKey} are equal, the returned map is empty unless
     * {@code fromInclusive} and {@code toInclusive} are both true.  The
     * returned map is backed by this map, so changes in the returned map are
     * reflected in this map, and vice-versa.  The returned map supports all
     * optional map operations that this map supports.
     * <p>
     * <p>The returned map will throw an {@code IllegalArgumentException}
     * on an attempt to insert a key outside of its range, or to construct a
     * submap either of whose endpoints lie outside its range.
     *
     * @param fromKey       low endpoint of the keys in the returned map
     * @param fromInclusive {@code true} if the low endpoint
     *                      is to be included in the returned view
     * @param toKey         high endpoint of the keys in the returned map
     * @param toInclusive   {@code true} if the high endpoint
     *                      is to be included in the returned view
     * @return a view of the portion of this map whose keys range from
     * {@code fromKey} to {@code toKey}
     * @throws ClassCastException       if {@code fromKey} and {@code toKey}
     *                                  cannot be compared to one another using this map's comparator
     *                                  (or, if the map has no comparator, using natural ordering).
     *                                  Implementations may, but are not required to, throw this
     *                                  exception if {@code fromKey} or {@code toKey}
     *                                  cannot be compared to keys currently in the map.
     * @throws NullPointerException     if {@code fromKey} or {@code toKey}
     *                                  is null and this map does not permit null keys
     * @throws IllegalArgumentException if {@code fromKey} is greater than
     *                                  {@code toKey}; or if this map itself has a restricted
     *                                  range, and {@code fromKey} or {@code toKey} lies
     *                                  outside the bounds of the range
     */
    @Override
    public NavigableMap<K, V> subMap(K fromKey, boolean fromInclusive, K toKey, boolean toInclusive)
    {
        BinaryNavMap<K, V> res = new BinaryNavMap<>();
        Iterator it = bst.iterator();
        while (it.hasNext())
        {
            Entry<K, V> n = (Entry<K, V>) it.next();
            K n_key = n.getKey();
            if ((fromInclusive ? (n_key.compareTo(fromKey) >= 0) : (n_key.compareTo(fromKey) > 0)) &&
                    (toInclusive ? (n_key.compareTo(toKey) <= 0) : (n_key.compareTo(toKey) < 0)))
                res.put(n_key, n.getValue());
        }

        return res;
    }

    /**
     * Returns a view of the portion of this map whose keys are less than (or
     * equal to, if {@code inclusive} is true) {@code toKey}.  The returned
     * map is backed by this map, so changes in the returned map are reflected
     * in this map, and vice-versa.  The returned map supports all optional
     * map operations that this map supports.
     * <p>
     * <p>The returned map will throw an {@code IllegalArgumentException}
     * on an attempt to insert a key outside its range.
     *
     * @param toKey     high endpoint of the keys in the returned map
     * @param inclusive {@code true} if the high endpoint
     *                  is to be included in the returned view
     * @return a view of the portion of this map whose keys are less than
     * (or equal to, if {@code inclusive} is true) {@code toKey}
     * @throws ClassCastException       if {@code toKey} is not compatible
     *                                  with this map's comparator (or, if the map has no comparator,
     *                                  if {@code toKey} does not implement {@link Comparable}).
     *                                  Implementations may, but are not required to, throw this
     *                                  exception if {@code toKey} cannot be compared to keys
     *                                  currently in the map.
     * @throws NullPointerException     if {@code toKey} is null
     *                                  and this map does not permit null keys
     * @throws IllegalArgumentException if this map itself has a
     *                                  restricted range, and {@code toKey} lies outside the
     *                                  bounds of the range
     */
    @Override
    public NavigableMap<K, V> headMap(K toKey, boolean inclusive)
    {
        BinaryNavMap<K, V> res = new BinaryNavMap<>();
        Iterator it = bst.iterator();
        while (it.hasNext())
        {
            Entry<K, V> n = (Entry<K, V>) it.next();
            K n_key = n.getKey();
            if ((inclusive ? (n_key.compareTo(toKey) <= 0) : (n_key.compareTo(toKey) < 0)))
                res.put(n_key, n.getValue());
        }

        return res;
    }

    /**
     * Returns a view of the portion of this map whose keys are greater than (or
     * equal to, if {@code inclusive} is true) {@code fromKey}.  The returned
     * map is backed by this map, so changes in the returned map are reflected
     * in this map, and vice-versa.  The returned map supports all optional
     * map operations that this map supports.
     * <p>
     * <p>The returned map will throw an {@code IllegalArgumentException}
     * on an attempt to insert a key outside its range.
     *
     * @param fromKey   low endpoint of the keys in the returned map
     * @param inclusive {@code true} if the low endpoint
     *                  is to be included in the returned view
     * @return a view of the portion of this map whose keys are greater than
     * (or equal to, if {@code inclusive} is true) {@code fromKey}
     * @throws ClassCastException       if {@code fromKey} is not compatible
     *                                  with this map's comparator (or, if the map has no comparator,
     *                                  if {@code fromKey} does not implement {@link Comparable}).
     *                                  Implementations may, but are not required to, throw this
     *                                  exception if {@code fromKey} cannot be compared to keys
     *                                  currently in the map.
     * @throws NullPointerException     if {@code fromKey} is null
     *                                  and this map does not permit null keys
     * @throws IllegalArgumentException if this map itself has a
     *                                  restricted range, and {@code fromKey} lies outside the
     *                                  bounds of the range
     */
    @Override
    public NavigableMap<K, V> tailMap(K fromKey, boolean inclusive)
    {
        BinaryNavMap<K, V> res = new BinaryNavMap<>();
        Iterator it = bst.iterator();
        while (it.hasNext())
        {
            Entry<K, V> n = (Entry<K, V>) it.next();
            K n_key = n.getKey();
            if ((inclusive ? (n_key.compareTo(fromKey) >= 0) : (n_key.compareTo(fromKey) > 0)))
                res.put(n_key, n.getValue());
        }

        return res;
    }

    /**
     * Returns the comparator used to order the keys in this map, or
     * {@code null} if this map uses the {@linkplain Comparable
     * natural ordering} of its keys.
     *
     * @return the comparator used to order the keys in this map,
     * or {@code null} if this map uses the natural ordering
     * of its keys
     */
    @Override
    public Comparator<? super K> comparator()
    {
        return null;
    }

    /**
     * {@inheritDoc}
     * <p>
     * <p>Equivalent to {@code subMap(fromKey, true, toKey, false)}.
     *
     * @param fromKey
     * @param toKey
     * @throws ClassCastException       {@inheritDoc}
     * @throws NullPointerException     {@inheritDoc}
     * @throws IllegalArgumentException {@inheritDoc}
     */
    @Override
    public SortedMap<K, V> subMap(K fromKey, K toKey)
    {
        return subMap(fromKey, true, toKey, false);
    }

    /**
     * {@inheritDoc}
     * <p>
     * <p>Equivalent to {@code headMap(toKey, false)}.
     *
     * @param toKey
     * @throws ClassCastException       {@inheritDoc}
     * @throws NullPointerException     {@inheritDoc}
     * @throws IllegalArgumentException {@inheritDoc}
     */
    @Override
    public SortedMap<K, V> headMap(K toKey)
    {
        return headMap(toKey, false);
    }

    /**
     * {@inheritDoc}
     * <p>
     * <p>Equivalent to {@code tailMap(fromKey, true)}.
     *
     * @param fromKey
     * @throws ClassCastException       {@inheritDoc}
     * @throws NullPointerException     {@inheritDoc}
     * @throws IllegalArgumentException {@inheritDoc}
     */
    @Override
    public SortedMap<K, V> tailMap(K fromKey)
    {
        return tailMap(fromKey, true);
    }

    /**
     * Returns the first (lowest) key currently in this map.
     *
     * @return the first (lowest) key currently in this map
     * @throws NoSuchElementException if this map is empty
     */
    @Override
    public K firstKey()
    {
        MyEntry<K, V> first = (MyEntry<K, V>) firstEntry();
        if (first == null)
            return null;
        else return (K) first.getKey();
    }

    /**
     * Returns the last (highest) key currently in this map.
     *
     * @return the last (highest) key currently in this map
     * @throws NoSuchElementException if this map is empty
     */
    @Override
    public K lastKey()
    {
        MyEntry<K, V> last = (MyEntry<K, V>) lastEntry();
        if (last == null)
            return null;
        else return (K) last.getKey();
    }
}