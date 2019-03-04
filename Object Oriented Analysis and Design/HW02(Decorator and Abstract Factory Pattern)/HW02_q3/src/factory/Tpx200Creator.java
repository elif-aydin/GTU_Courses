package factory;

import plane.Plane;
import plane.Tpx200;

/**
 * Concrete Factory implementation for TPX 200.
 */
public class Tpx200Creator extends Factory {
    /**
     * Creates a plane with basic configuration.
     * @return a plane
     */
    @Override
    protected Plane getBasicPlane() {
        return new Tpx200();
    }

    /**
     * Constructs the skeleton of plane.
     * @param plane plane to construct skeleton.
     */
    @Override
    protected void constructSkeleton(Plane plane) {
        plane.setSkeleton("Nickel alloy alloy");
    }

    /**
     * Places engines of plane.
     * @param plane plane to place engines.
     */
    @Override
    protected void placeEngines(Plane plane) {
        plane.setEngine("Twin jet engines");
    }

    /**
     * Places the seats of plane.
     * @param plane plane to place seats.
     */
    @Override
    protected void placeSeats(Plane plane) {
        plane.setSeats("100 seats");
    }
}
