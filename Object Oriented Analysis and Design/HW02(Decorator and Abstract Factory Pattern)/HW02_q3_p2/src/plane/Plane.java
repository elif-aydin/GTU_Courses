package plane;

/**
 * Base Class to represent all planes.
 */
public abstract class Plane {
    private String skeleton;
    private String engine;
    private String seats;
    private String engineInjectionType;
    private String seatingCover;

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

    /**
     * Gets the engine injection type.
     * @return engineInjectionType
     */
    public String getEngineInjectionType() {
        return engineInjectionType;
    };

    /**
     * Gets the seating cover.
     * @return seatingCover
     */
    public String getSeatingCover() {
        return seatingCover;
    };

    /**
     * Sets the engine injection type.
     * @param engineInjectionType type to set.
     */
    public void setEngineInjectionType(String engineInjectionType) {
        this.engineInjectionType = engineInjectionType;
    }

    /**
     * Sets the seating cover.
     * @param seatingCover type to set.
     */
    public void setSeatingCover(String seatingCover) {
        this.seatingCover = seatingCover;
    }

    @Override
    public String toString() {
        return  "Name             : " + getName() + "\n" +
                "Skeleton         : " + skeleton + "\n" +
                "Engine           : " + engine + "\n" +
                "Seats            : " + seats + "\n" +
                "Engine Injection : " + engineInjectionType + "\n" +
                "Seating Cover    : " + seatingCover;
    }
}
