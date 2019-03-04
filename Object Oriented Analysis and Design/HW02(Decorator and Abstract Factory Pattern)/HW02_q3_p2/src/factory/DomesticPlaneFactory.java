package factory;

import plane.Plane;

/**
 * Concrete factory for Domestic planes.
 */
public class DomesticPlaneFactory implements AbstractFactory {
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

    public DomesticPlaneFactory() {
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
        return applyDomestic(tpx100Creator.createPlane());
    }

    /**
     * Create a TPX 200 plane
     * @return TPX 200 plane
     */
    @Override
    public Plane createTpx200Plane() {
        return applyDomestic(tpx200Creator.createPlane());
    }

    /**
     * Create a TPX 300 plane
     * @return TPX 300 plane
     */
    @Override
    public Plane createTpx300Plane() {
        return applyDomestic(tpx300Creator.createPlane());
    }

    /**
     * Apply the domestic logic to the plane.
     * @param plane plane to customize
     * @return customized plane
     */
    private Plane applyDomestic(Plane plane) {
        plane.setEngineInjectionType("Turbojet");
        plane.setSeatingCover("Velvet");
        return plane;
    }
}
