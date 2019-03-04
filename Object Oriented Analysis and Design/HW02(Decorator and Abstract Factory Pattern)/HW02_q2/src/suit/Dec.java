package suit;

/**
 * Concrete implementation of Dec Suit.
 */
public class Dec implements Suit {
    @Override
    public Double getPrice() {
        return 500.0;
    }

    @Override
    public Double getWeight() {
        return 25.0;
    }
}
