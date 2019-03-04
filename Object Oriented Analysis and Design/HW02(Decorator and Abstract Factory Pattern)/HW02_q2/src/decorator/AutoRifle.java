package decorator;

import suit.Suit;

/**
 * Concrete AutoRifle implementation.
 */
public class AutoRifle extends BaseAccessory {
    /**
     * Constructor to accept a suit.
     * @param wrappee suit to wrap
     */
    public AutoRifle(Suit wrappee) {
        super(wrappee);
    }

    @Override
    public Double getPrice() {
        return super.getPrice() + 30.0;
    }

    @Override
    public Double getWeight() {
        return super.getWeight() + 1.5;
    }
}
