package plane;

/**
 * Base Class to represent all planes.
 */
public abstract class Plane {
    private String skeleton;
    private String engine;
    private String seats;


    /**
     * All concrete planes will implement this different.
     * @return  name of the plane
     */
    public abstract String getName();

    /**
     * Gets the skeleton.
     * @return skeleton
     */
    public String getSkeleton() {
        return skeleton;
    }

    /**
     * Sets the skeleton.
     * @param skeleton skeleton to set.
     */
    public void setSkeleton(String skeleton) {
        this.skeleton = skeleton;
    }

    /**
     * Gets the engine.
     * @return engine
     */
    public String getEngine() {
        return engine;
    }

    /**
     * Sets the engine.
     * @param engine engine to set.
     */
    public void setEngine(String engine) {
        this.engine = engine;
    }

    /**
     * Gets the seats.
     * @return seats
     */
    public String getSeats() {
        return seats;
    }

    /**
     * Sets the seats.
     * @param seats seats to set.
     */
    public void setSeats(String seats) {
        this.seats = seats;
    }

    @Override
    public String toString() {
        return  "Name      : " + getName() + "\n" +
                "Skeleton  : " + skeleton + "\n" +
                "Engine    : " + engine + "\n" +
                "Seats     : " + seats;
    }
}
