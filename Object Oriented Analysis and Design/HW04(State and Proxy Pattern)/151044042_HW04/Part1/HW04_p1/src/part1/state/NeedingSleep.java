/*
 * Created by elifs on 12/22/2018.
 */

package part1.state;

import part1.Student;

/**
 * Class for needing sleep state
 */
public class NeedingSleep implements State {
    private Student student;

    /**
     * Constructor for needing sleep
     *
     * @param student set for student
     */
    public NeedingSleep(Student student) {
        this.student = student;
    }

    /**
     * Implementation of hardWorkAndPerseverance function for
     * Needing Sleep state
     */
    @Override
    public void hardWorkAndPerseverance() {
        System.out.println("Called hardWorkAndPerseverance >> You can't hard work and you can't have perseverance!");
    }

    /**
     * Implementation of exercise function for
     * Needing Sleep state
     */
    @Override
    public void exercise() {
        System.out.println("Called Exercise >> You can't do exercise!");
    }

    /**
     * Implementation of cheating function for
     * Needing Sleep state
     */
    @Override
    public void cheating() {
        System.out.println("Called Cheating >> You can't cheat!");
    }

    /**
     * Implementation of sleep function for
     * Needing Sleep state
     */
    @Override
    public void sleep() {
        System.out.println("Called Sleep >> You are ready now!");
        student.setState(student.getReady());
    }

    /**
     * Implementation of buyingGTX1080 function for
     * Needing Sleep state
     */
    @Override
    public void buyingGTX1080() {
        System.out.println("Called BuyingGTX1080 >> You can't buy a GTX 1080 :(");
    }

    /**
     * Implementation of outTillLate function for
     * Needing Sleep state
     */
    @Override
    public void outTillLate() {
        System.out.println("Called OutTillLate >> You can't wait out till late!");
    }

    /**
     * Implementation of coffeeAndWork function for
     * Needing Sleep state
     */
    @Override
    public void coffeeAndWork() {
        System.out.println("Called coffeeAndWork >> You have a chronic illness now :(!");
        student.setState(student.getChronicIllness());
    }

    /**
     * Implementation of toString
     *
     * @return String value for needing sleep class
     */
    public String toString() {
        return "State : Needing Sleep";
    }
}
