package decorator;

import suit.Suit;

/**
 * Concrete Laser implementation.
 */
public class Laser extends BaseAccessory {
    /**
     * Constructor to accept a suit.
     * @param wrappee suit to wrap
     */
    public Laser(Suit wrappee) {
        super(wrappee);
    }

    @Override
    public Double getPrice() {
        return super.getPrice() + 200.0;
    }

    @Override
    public Double getWeight() {
        return super.getWeight() + 5.5;
    }
}
