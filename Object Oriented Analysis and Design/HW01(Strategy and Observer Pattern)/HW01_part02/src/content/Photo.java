package content;

public class Photo implements Content {
    private String path;
    public Photo(String path) {
        this.path = path;
    }

    @Override
    public String toString() {
        return path;
    }
}
