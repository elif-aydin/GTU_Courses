package suit;

/**
 * Concrete implementation of Ora Suit.
 */
public class Tor implements Suit {
    @Override
    public Double getPrice() {
        return 5000.0;
    }

    @Override
    public Double getWeight() {
        return 50.0;
    }
}
