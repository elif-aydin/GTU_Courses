import factory.Factory;
import factory.Tpx100Creator;
import factory.Tpx200Creator;
import factory.Tpx300Creator;
import plane.Plane;

public class Main {

    public static void main(String[] args) {
        Factory tpx100Creator = new Tpx100Creator();
        Factory tpx200Creator = new Tpx200Creator();
        Factory tpx300Creator = new Tpx300Creator();

        Plane tpx100 = tpx100Creator.createPlane();
        System.out.println(tpx100);
        System.out.println();

        Plane tpx200 = tpx200Creator.createPlane();
        System.out.println(tpx200);
        System.out.println();

        Plane tpx300 = tpx300Creator.createPlane();
        System.out.println(tpx300);
    }
}
