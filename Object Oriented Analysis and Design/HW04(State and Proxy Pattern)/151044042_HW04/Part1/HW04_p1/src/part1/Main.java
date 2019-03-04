/*
 * Created by elifs on 12/22/2018.
 */

package part1;

public class Main {
    public static void main(String[] args) {
        System.out.println("******** Ready -> Fit ********");
        Student student = new Student();
        System.out.println(student.getState());
        student.exercise();
        System.out.println(student.getState());

        System.out.println("\n******** Ready -> Fit -> Graduate ********");
        student = new Student();
        System.out.println(student.getState());
        student.exercise();
        System.out.println(student.getState());
        student.hardWorkAndPerseverance();
        System.out.println(student.getState());

        System.out.println("\n******** Ready -> Unable To Become A Rod For An Axe ********");
        student = new Student();
        System.out.println(student.getState());
        student.cheating();
        System.out.println(student.getState());
        System.out.println("****************");
        student = new Student();
        System.out.println(student.getState());
        student.buyingGTX1080();
        System.out.println(student.getState());

        System.out.println("\n******** Ready -> Needing Sleep -> Chronic Illness ********");
        student = new Student();
        System.out.println(student.getState());
        student.outTillLate();
        System.out.println(student.getState());
        student.coffeeAndWork();
        System.out.println(student.getState());

        System.out.println("\n******** Ready -> Needing Sleep -> Ready ********");
        student = new Student();
        System.out.println(student.getState());
        student.outTillLate();
        System.out.println(student.getState());
        student.sleep();
        System.out.println(student.getState());

        System.out.println("\n******** Unsupported Operations ********");

        student = new Student();
        System.out.println(student.getState());
        student.coffeeAndWork();
        System.out.println(student.getState());
        student.sleep();
        System.out.println(student.getState());
    }
}
