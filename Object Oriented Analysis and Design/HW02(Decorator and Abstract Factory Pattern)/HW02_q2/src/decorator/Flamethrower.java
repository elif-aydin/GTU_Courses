package decorator;

import suit.Suit;

/**
 * Concrete Flamethrower implementation.
 */
public class Flamethrower extends BaseAccessory {
    /**
     * Constructor to accept a suit.
     * @param wrappee suit to wrap
     */
    public Flamethrower(Suit wrappee) {
        super(wrappee);
    }

    @Override
    public Double getPrice() {
        return super.getPrice() + 50.0;
    }

    @Override
    public Double getWeight() {
        return super.getWeight() + 2.0;
    }
}
