package decorator;

import suit.Suit;

/**
 * Middle class that connects decorators with suits. Implements the Suit interface like a real suit.
 */
public class BaseAccessory implements Suit {
    /**
     * A suit to wrap.
     */
    private Suit wrappee;

    /**
     * Constructor to accept a suit.
     * @param wrappee suit to wrap
     */
    public BaseAccessory(Suit wrappee) {
        this.wrappee = wrappee;
    }

    @Override
    public Double getPrice() {
        return wrappee.getPrice();
    }

    @Override
    public Double getWeight() {
        return wrappee.getWeight();
    }
}
