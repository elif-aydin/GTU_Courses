/*
 * Created by elifs on 12/22/2018.
 */

package part1;

import part1.state.*;

public class Student {
    private State graduate;
    private State fit;
    private State ready;
    private State needingSleep;
    private State chronicIllness;
    private State unableToBecomeARodForAnAxe;

    private State state;

    public Student() {
        graduate = new Graduate(this);
        fit = new Fit(this);
        ready = new Ready(this);
        needingSleep = new NeedingSleep(this);
        chronicIllness = new ChronicIllness(this);
        unableToBecomeARodForAnAxe = new UnableToBecomeARodForAnAxe(this);

        state = ready;   //initial status
    }

    public State getGraduate() {
        return graduate;
    }

    public State getFit() {
        return fit;
    }

    public State getReady() {
        return ready;
    }

    public State getNeedingSleep() {
        return needingSleep;
    }

    public State getChronicIllness() {
        return chronicIllness;
    }

    public State getUnableToBecomeARodForAnAxe() {
        return unableToBecomeARodForAnAxe;
    }

    public void coffeeAndWork() {
        state.coffeeAndWork();
    }

    public void sleep() {
        state.sleep();
    }

    public void outTillLate() {
        state.outTillLate();
    }

    public void hardWorkAndPerseverance() {
        state.hardWorkAndPerseverance();
    }

    public void exercise() {
        state.exercise();
    }

    public void buyingGTX1080() {
        state.buyingGTX1080();
    }

    public void cheating() {
        state.cheating();
    }

    public void setState(State state) {
        this.state = state;
    }

    public String getState() {
        return state.toString();
    }
}