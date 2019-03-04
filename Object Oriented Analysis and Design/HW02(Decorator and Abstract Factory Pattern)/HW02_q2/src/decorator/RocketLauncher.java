package decorator;

import suit.Suit;

/**
 * Concrete RocketLauncher implementation.
 */
public class RocketLauncher extends BaseAccessory {
    /**
     * Constructor to accept a suit.
     * @param wrappee suit to wrap
     */
    public RocketLauncher(Suit wrappee) {
        super(wrappee);
    }

    @Override
    public Double getPrice() {
        return super.getPrice() + 150.0;
    }

    @Override
    public Double getWeight() {
        return super.getWeight() + 7.5;
    }
}
