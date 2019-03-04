/**
 * The common component of the Composite Pattern.
 */
public interface Email {
    /**
     * Common method of all objects, either single or composite object.
     * @return String representation of this address.
     */
    public String getAsStr();
}
