package suit;

/**
 * Common interface for both actual suits and decorators
 */
public interface Suit {
    /**
     * Gets the price of suit.
     * @return price
     */
    public Double getPrice();

    /**
     * Gets the weight of suit.
     * @return weight
     */
    public Double getWeight();
}
