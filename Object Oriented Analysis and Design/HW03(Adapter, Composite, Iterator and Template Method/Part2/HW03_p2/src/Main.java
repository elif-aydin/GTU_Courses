public class Main
{

    public static void main(String[] args) {
        Email e1 = new PersonalEmail("abc@abc.com", "Abc abc");
        Email e2 = new PersonalEmail("def@abc.com", "def def");
        Email e3 = new PersonalEmail("fhi@abc.com", "fhi fhi");
        System.out.print("A single email: ");
        System.out.println(e1.getAsStr());
        System.out.println();

        System.out.println("A group email address that contains the above single and some others:");
        Email g1 = new GroupEmail("group@group.com", "We are a group!");
        ((GroupEmail) g1).addAll(e1, e2, e3);

        System.out.println(g1.getAsStr());
    }
}
