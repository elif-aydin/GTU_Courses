package suit;

/**
 * Concrete implementation of Ora Suit.
 */
public class Ora implements Suit {
    @Override
    public Double getPrice() {
        return 1500.0;
    }

    @Override
    public Double getWeight() {
        return 30.0;
    }
}
