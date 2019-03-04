import factory.*;
import plane.Plane;

public class Main {

    public static void main(String[] args) {
        AbstractFactory f = new DomesticPlaneFactory();

        System.out.println("Domestic 100: ");
        Plane tpx100 = f.createTpx100Plane();
        System.out.println(tpx100);
        System.out.println();

        f = new EurasiaPlaneFactory();
        Plane tpx200 = f.createTpx200Plane();
        System.out.println("Eurasia 200: ");
        System.out.println(tpx200);
        System.out.println();

        f = new OtherPlaneFactory();
        Plane tpx300 = f.createTpx300Plane();
        System.out.println("Other 300: ");
        System.out.println(tpx300);
    }
}
