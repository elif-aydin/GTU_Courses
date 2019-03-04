package factory;

import plane.Plane;

/**
 * Concrete factory for Other planes.
 */
public class OtherPlaneFactory implements AbstractFactory {
    /**
     * Factory to create actual TPX 100.
     */
    private Tpx100Creator tpx100Creator;

    /**
     * Factory to create actual TPX 200.
     */
    private Tpx200Creator tpx200Creator;

    /**
     * Factory to create actual TPX 300.
     */
    private Tpx300Creator tpx300Creator;

    public OtherPlaneFactory() {
        tpx100Creator = new Tpx100Creator();
        tpx200Creator = new Tpx200Creator();
        tpx300Creator = new Tpx300Creator();
    }

    /**
     * Create a TPX 100 plane
     * @return TPX 100 plane
     */
    @Override
    public Plane createTpx100Plane() {
        return applyOther(tpx100Creator.createPlane());
    }

    /**
     * Create a TPX 200 plane
     * @return TPX 200 plane
     */
    @Override
    public Plane createTpx200Plane() {
        return applyOther(tpx200Creator.createPlane());
    }

    /**
     * Create a TPX 300 plane
     * @return TPX 300 plane
     */
    @Override
    public Plane createTpx300Plane() {
        return applyOther(tpx300Creator.createPlane());
    }

    /**
     * Apply the other planes' logic to the plane.
     * @param plane plane to customize
     * @return customized plane
     */
    private Plane applyOther(Plane plane) {
        plane.setEngineInjectionType("Geared turbofan");
        plane.setSeatingCover("Leather");
        return plane;
    }
}
