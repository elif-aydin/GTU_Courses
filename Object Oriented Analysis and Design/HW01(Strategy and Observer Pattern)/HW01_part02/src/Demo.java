import content.ContentType;
import observer.Observer;

public class Demo {
    public static void main(String[] args) {
        NewContentPublisher newContentPublisher = new NewContentPublisher();
        Observer o1 = new Observer("Karen");
        Observer o2 = new Observer("Derek");
        Observer o3 = new Observer("Jack");

        newContentPublisher.getManager().subscribe(ContentType.TEXT, o1);

        newContentPublisher.getManager().subscribe(ContentType.TEXT, o2);
        newContentPublisher.getManager().subscribe(ContentType.PHOTO, o2);

        newContentPublisher.getManager().subscribe(ContentType.TEXT, o3);
        newContentPublisher.getManager().subscribe(ContentType.PHOTO, o3);
        newContentPublisher.getManager().subscribe(ContentType.AUDIO, o3);

        System.out.println("Testing text:");
        newContentPublisher.newTextContent("text1.txt");
        System.out.println();

        System.out.println("Testing photo:");
        newContentPublisher.newPhotoContent("photo1.png");
        System.out.println();

        System.out.println("Testing audio:");
        newContentPublisher.newAudioContent("audio1.png");
        System.out.println();
    }
}
