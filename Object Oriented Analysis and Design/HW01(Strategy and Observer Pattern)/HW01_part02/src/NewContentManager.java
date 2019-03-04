import content.Content;
import content.ContentType;
import observer.Observer;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class NewContentManager {
    private Map<ContentType, List<Observer>> subscribers = new HashMap<>();

    public NewContentManager(ContentType... operations) {
        for (ContentType operation : operations) {
            this.subscribers.put(operation, new ArrayList<>());
        }
    }

    public void subscribe(ContentType contentType, Observer listener) {
        List<Observer> users = subscribers.get(contentType);
        users.add(listener);
    }

    public void unsubscribe(ContentType contentType, Observer listener) {
        List<Observer> users = subscribers.get(contentType);
        int index = users.indexOf(listener);
        users.remove(index);
    }

    public void notify(ContentType contentType, Content content) {
        List<Observer> users = subscribers.get(contentType);
        for (Observer subscriber : users) {
            subscriber.update(contentType, content);
        }
    }
}
