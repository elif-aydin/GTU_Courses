/*
 * Created by elifs on 12/22/2018.
 */

package part1.state;

import part1.Student;

/**
 * Class for needing ready state
 */
public class Ready implements State {
    private Student student;

    /**
     * Constructor for ready
     *
     * @param student set for student
     */
    public Ready(Student student) {
        this.student = student;
    }

    /**
     * Implementation of hardWorkAndPerseverance function for
     * Ready state
     */
    @Override
    public void hardWorkAndPerseverance() {
        System.out.println("Called hardWorkAndPerseverance >> Congrats you are graduate!");
        student.setState(student.getGraduate());
    }

    /**
     * Implementation of exercise function for
     * Ready state
     */
    @Override
    public void exercise() {
        System.out.println("Called Exercise >> Congrats you are fit!");
        student.setState(student.getFit());
    }

    /**
     * Implementation of cheating function for
     * Ready state
     */
    @Override
    public void cheating() {
        System.out.println("Called Cheating >> Sorry. You are unable to become a rod for an axe :(");
        student.setState(student.getUnableToBecomeARodForAnAxe());
    }

    /**
     * Implementation of sleep function for
     * Ready state
     */
    @Override
    public void sleep() {
        System.out.println("Called Sleep >> You can't sleep!");
    }

    /**
     * Implementation of buyingGTX1080 function for
     * Ready state
     */
    @Override
    public void buyingGTX1080() {
        System.out.println("Called BuyingGTX1080 >> Sorry. You are unable to become a rod for an axe :(");
        student.setState(student.getUnableToBecomeARodForAnAxe());
    }

    /**
     * Implementation of outTillLate function for
     * Ready state
     */
    @Override
    public void outTillLate() {
        System.out.println("Called OutTillLate >> You need to sleep now");
        student.setState(student.getNeedingSleep());
    }

    /**
     * Implementation of coffeeAndWork function for
     * Ready state
     */
    @Override
    public void coffeeAndWork() {
        System.out.println("Called coffeeAndWork >> You can't drink a coffee and you cant work!");
    }

    /**
     * Implementation of toString
     *
     * @return String value for ready class
     */
    public String toString() {
        return "State : Ready";
    }

}
