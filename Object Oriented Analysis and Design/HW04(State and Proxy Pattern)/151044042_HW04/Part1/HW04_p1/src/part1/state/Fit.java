/*
 * Created by elifs on 12/22/2018.
 */

package part1.state;

import part1.Student;

/**
 * Class for fit state
 */
public class Fit implements State {
    private Student student;

    /**
     * Constructor for fit
     *
     * @param student set for student
     */
    public Fit(Student student) {
        this.student = student;
    }

    /**
     * Implementation of hardWorkAndPerseverance function for
     * Fit state
     */
    @Override
    public void hardWorkAndPerseverance() {
        System.out.println("Called hardWorkAndPerseverance >> Congrats you graduate!");
        student.setState(student.getGraduate());
    }

    /**
     * Implementation of exercise function for
     * Fit state
     */
    @Override
    public void exercise() {
        System.out.println("Called Exercise >> You can't do exercise!");
    }

    /**
     * Implementation of cheating function for
     * Fit state
     */
    @Override
    public void cheating() {
        System.out.println("Called Cheating >> You can't cheat!");
    }

    /**
     * Implementation of sleep function for
     * Fit state
     */
    @Override
    public void sleep() {
        System.out.println("Called Sleep >> You can't sleep!");
    }

    /**
     * Implementation of buyingGTX1080 function for
     * Fit state
     */
    @Override
    public void buyingGTX1080() {
        System.out.println("Called BuyingGTX1080 >> You can't buy a GTX 1080 :(");
    }

    /**
     * Implementation of outTillLate function for
     * Fit state
     */
    @Override
    public void outTillLate() {
        System.out.println("Called OutTillLate >> You can't wait out till late!");
    }

    /**
     * Implementation of coffeeAndWork function for
     * Fit state
     */
    @Override
    public void coffeeAndWork() {
        System.out.println("Called coffeeAndWork >> You can't drink a coffee and you cant work!");
    }

    /**
     * Implementation of toString
     *
     * @return String value for fit class
     */
    public String toString() {
        return "State : Fit";
    }
}
