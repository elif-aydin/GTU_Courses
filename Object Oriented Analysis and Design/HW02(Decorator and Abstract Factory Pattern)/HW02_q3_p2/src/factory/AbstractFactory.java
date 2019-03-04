package factory;

import plane.*;

/**
 * Interface for concrete factories.
 */
public interface AbstractFactory {
    /**
     * Create a TPX 100 plane
     * @return TPX 100 plane
     */
    public Plane createTpx100Plane();

    /**
     * Create a TPX 200 plane
     * @return TPX 200 plane
     */
    public Plane createTpx200Plane();

    /**
     * Create a TPX 300 plane
     * @return TPX 300 plane
     */
    public Plane createTpx300Plane();
}
