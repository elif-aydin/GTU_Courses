import decorator.AutoRifle;
import decorator.Flamethrower;
import decorator.Laser;
import decorator.RocketLauncher;
import suit.*;

public class Main {

    public static void main(String[] args) {
        Suit s = new Dec();
        System.out.println("A dec: " + suitStr(s));

        Suit f = new Flamethrower(s);
        System.out.println("A dec with Flamethrower: " + suitStr(f));

        Suit a = new AutoRifle(s);
        System.out.println("A dec with AutoRifle: " + suitStr(a));

        Suit combo = new AutoRifle(f);
        System.out.println("A dec with Flamethrower and AutoRifle: " + suitStr(combo));

        System.out.println();

        s = new Tor();
        System.out.println("A tor: " + suitStr(s));

        f = new Flamethrower(s);
        System.out.println("A tor with Flamethrower: " + suitStr(f));

        combo = new Laser(new RocketLauncher(new AutoRifle(f)));
        System.out.println("A tor with Flamethrower, AutoRifle, RocketLauncher and Laser: " + suitStr(combo));

        combo = new Flamethrower(combo);
        System.out.println("A tor with 2 Flamethrower, 1 AutoRifle and 1 RocketLauncher: " + suitStr(combo));
    }

    private static String suitStr(Suit s) {
        return s.getPrice() + "k TL, " + s.getWeight() + " kg";
    }
}
