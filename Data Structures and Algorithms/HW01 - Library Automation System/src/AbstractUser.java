import java.util.Objects;

/**
 * Created by elif on 18-Feb-17.
 * This method help us to implemet inteface's functions
 */
public abstract class AbstractUser implements User
{
    private String name;
    private String surname;
    private String ID ;
    private String password;

    /**
     * AbstractUser's no parameter constructor for initialize
     */
    public AbstractUser()
    {
        this.name = null;
        this.surname = null;
        this.ID = null;
        this.password = null;
    }

    /**
     * User Constructor
     *
     * @param name user's name
     * @param surname user's surname
     * @param ID user's ID
     * @param password user's password
     */
    public AbstractUser(String name, String surname, String ID, String password)
    {
        this.name = name;
        this.surname = surname;
        this.ID = ID;
        this.password = password;
    }

    /**
     * Takes user to copy it.
     * @param user AbstractUser object to initialize
     */
    public AbstractUser(AbstractUser user)
    {
        name = user.getUserName();
        surname = user.getUserSurname();
        ID = user.getID();
        password = user.getPassword();
    }

    /**
     * This method return user name
     * @return user's name
     */
    public String getUserName()
    {
        return name;
    }

    /**
     * This method set user name
     * @param name user's name
     */
    public void setUserName(String name)
    {
        this.name = name;
    }

    /**
     * This method return user surname
     * @return user's surname
     */
    public String getUserSurname()
    {
        return surname;
    }

    /**
     * This method set user surname
     * @param surname AbstractUser's surname
     */
    public void setUserSurname(String surname)
    {
        this.surname = surname;
    }

    /**
     * This method return user ID
     * @return AbstractUser's ID
     */
    public String getID()
    {
        return ID;
    }

    /**
     * This method set user ID
     * @param ID user's ID
     */
    public void setID(String ID)
    {
        this.ID = ID;
    }

    /**
     * This method return user password
     * @return AbstractUser's password
     */
    public String getPassword()
    {
        return password;
    }

    /**
     * This method set user password
     * @param password
     */
    public void setPassword(String password)
    {
        this.password = password;
    }

    /**
     * This method overrided from object class
     * @return Information of user
     */
    @Override
    public String toString()
    {
        String newString;
        newString = name + "," + surname + "," + ID + "," + password;

        return newString;
    }

    /**
     * This methods compares two user objects
     * @param o Compare object
     * @return result of comparision
     */
    @Override
    public boolean equals(Object o)
    {
        if(this == o)
            return true;

        if(o == null && o.getClass() != this.getClass())
            return false;

        AbstractUser user = (AbstractUser)o;

        return Objects.equals(name, user.getUserName()) &&
                Objects.equals(surname, user.getUserSurname()) &&
                Objects.equals(ID, user.getID()) &&
                Objects.equals(password, user.getPassword());
    }
}