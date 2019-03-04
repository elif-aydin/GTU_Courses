package factory;

import plane.Plane;

/**
 * Base Class for Creators/Factories. Contains logic of creating a plane.
 */
public abstract class Factory {

    /**
     * Creates a plane by applying logic.
     * @return plane
     */
    public Plane createPlane() {
        Plane plane = getBasicPlane();

        constructSkeleton(plane);
        placeEngines(plane);
        placeSeats(plane);
        return plane;
    }

    /**
     * Creates a plane with basic configuration. Each concrete class will implement.
     * @return a plane
     */
    protected abstract Plane getBasicPlane();

    /**
     * Constructs the skeleton of plane. Each concrete class will implement.
     * @param plane plane to construct skeleton.
     */
    protected abstract void constructSkeleton(Plane plane);

    /**
     * Places engines of plane. Each concrete class will implement.
     * @param plane plane to place engines.
     */
    protected abstract void placeEngines(Plane plane);

    /**
     * Places the seats of plane. Each concrete class will implement.
     * @param plane plane to place seats.
     */
    protected abstract void placeSeats(Plane plane);
}
