package factory;

import plane.Plane;
import plane.Tpx300;

/**
 * Concrete PlaneFactory implementation for TPX 300.
 */
public class Tpx300Creator extends PlaneFactory {
    /**
     * Creates a plane with basic configuration.
     * @return a plane
     */
    @Override
    protected Plane getBasicPlane() {
        return new Tpx300();
    }

    /**
     * Constructs the skeleton of plane.
     * @param plane plane to construct skeleton.
     */
    @Override
    protected void constructSkeleton(Plane plane) {
        plane.setSkeleton("Titanium alloy alloy");
    }

    /**
     * Places engines of plane.
     * @param plane plane to place engines.
     */
    @Override
    protected void placeEngines(Plane plane) {
        plane.setEngine("Quadro jet engines");
    }

    /**
     * Places the seats of plane.
     * @param plane plane to place seats.
     */
    @Override
    protected void placeSeats(Plane plane) {
        plane.setSeats("250 seats");
    }
}
