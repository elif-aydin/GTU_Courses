/**
 * Created by elif on 18-Feb-17.
 *
 * This interface is gonna use for users on the library management system.
 * We will create users information to override this methods.
 */
public interface User
{
    /**
     * This method return name of user
     * @return user name
     */
    String getUserName();

    /**
     * This method set user name
     * @param userName user's name
     */
    void setUserName(String userName);

    /**
     * This method return surname of user
     * @return user surname
     */
    String getUserSurname();

    /**
     * This method set user surname
     * @param surname user's surname
     */
    void setUserSurname(String surname);

    /**
     * This method return ID of user
     * @return userID
     */
    String getID();

    /**
     * This method set user ID
     * @param ID user's ID
     */
    void setID(String ID);

    /**
     * This method return password of user
     * @return user's password
     */
    String getPassword();

    /**
     * This method set user password
     * @param password user's password
     */
    void setPassword(String password);

    /**
     * This method use for choice
     * @return choice user's choice for
     */
    int menu();
}