package observer;

import content.Content;
import content.ContentType;

public class Observer {
    private String name;
    public Observer(String name) {
        this.name = name;
    }

    public void update(ContentType contentType, Content content) {
        System.out.println("I am " + this.name + ". I got a new " + contentType.name() + " content here: " + content.toString());
    }
}
