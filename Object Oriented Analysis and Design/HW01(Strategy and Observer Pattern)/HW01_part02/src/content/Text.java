package content;

public class Text implements Content {
    private String path;
    public Text(String path) {
        this.path = path;
    }

    @Override
    public String toString() {
        return path;
    }
}
