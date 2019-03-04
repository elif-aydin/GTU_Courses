import content.*;

public class NewContentPublisher {
    private NewContentManager manager;
    private Content content;

    public NewContentPublisher() {
        this.manager = new NewContentManager(ContentType.values());
    }

    public NewContentManager getManager() {
        return manager;
    }

    public void newTextContent(String contentPath) {
        this.content = new Text(contentPath);
        manager.notify(ContentType.TEXT, content);
    }

    public void newPhotoContent(String contentPath) {
        this.content = new Photo(contentPath);
        manager.notify(ContentType.PHOTO, content);
    }

    public void newAudioContent(String contentPath) {
        this.content = new Audio(contentPath);
        manager.notify(ContentType.AUDIO, content);
    }
}
