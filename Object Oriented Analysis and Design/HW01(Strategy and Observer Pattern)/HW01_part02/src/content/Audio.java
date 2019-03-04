package content;

public class Audio implements Content {
    private String path;

    public Audio(String path) {
        this.path = path;
    }

    @Override
    public String toString() {
        return path;
    }
}
