import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Composite type of email address. Contains multiple email addresses as well as a single representation (group address
 * and name).
 */
public class GroupEmail extends PersonalEmail {

    /**
     * Children email addresses that this address contain.
     */
    private List<Email> children;

    /**
     * Constructor to initialize composite address.
     * @param emailAddress  group email address
     * @param name  name of the group
     */
    public GroupEmail(String emailAddress, String name) {
        super(emailAddress, name);
        children = new ArrayList<Email>();
    }

    /**
     * Adds a child email address to the group.
     * @param email address to be added.
     */
    public void add(Email email) {
     children.add(email);
    }

    /**
     * Same as @add method, works for multiple addresses.
     * @param emails    addresses to be added.
     */
    public void addAll(Email ... emails) {
        children.addAll(Arrays.asList(emails));
    }

    /**
     * Delete an email from the children.
     * @param email
     */
    public void remove(Email email) {
        children.remove(email);
    }

    /**
     * Gets all child addresses that composite contains.
     * @return list of child email addresses
     */
    public List<Email> getChildren()
    {
        return this.children;
    }

    /**
     * Common method implementation for the group email addresses. Calls child common methods to build a result.
     * @return  String representation of this group mail address (with all children).
     */
    @Override
    public String getAsStr() {
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(super.getAsStr()).append("\n");
        for (Email email: children) {
            stringBuilder.append(email.getAsStr()).append("\n");
        }

        return stringBuilder.toString();
    }
}
