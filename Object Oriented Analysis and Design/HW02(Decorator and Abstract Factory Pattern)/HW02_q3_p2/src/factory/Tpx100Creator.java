package factory;

import plane.Plane;
import plane.Tpx100;

/**
 * Concrete PlaneFactory implementation for TPX 100.
 */
public class Tpx100Creator extends PlaneFactory {
    /**
     * Creates a plane with basic configuration.
     * @return a plane
     */
    @Override
    protected Plane getBasicPlane() {
        return new Tpx100();
    }

    /**
     * Constructs the skeleton of plane.
     * @param plane plane to construct skeleton.
     */
    @Override
    protected void constructSkeleton(Plane plane) {
        plane.setSkeleton("Aluminum alloy");
    }

    /**
     * Places engines of plane.
     * @param plane plane to place engines.
     */
    @Override
    protected void placeEngines(Plane plane) {
        plane.setEngine("Single jet engine");
    }

    /**
     * Places the seats of plane.
     * @param plane plane to place seats.
     */
    @Override
    protected void placeSeats(Plane plane) {
        plane.setSeats("50 seats");
    }
}
