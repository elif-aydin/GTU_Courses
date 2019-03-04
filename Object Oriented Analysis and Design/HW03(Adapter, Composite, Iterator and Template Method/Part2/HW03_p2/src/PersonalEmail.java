/**
 * The single type object. Represents a single email address.
 */
public class PersonalEmail implements Email {
    private String emailAddress;
    private String name;

    /**
     * Constructor to initialize the email address.
     * @param emailAddress  address
     * @param name  name of this address
     */
    public PersonalEmail(String emailAddress, String name) {
        this.emailAddress = emailAddress;
        this.name = name;
    }

    /**
     * Common method implementation of this single email address.
     * @return String representation of this address.
     */
    @Override
    public String getAsStr() {
        return this.emailAddress + " " + this.name ;
    }
}
