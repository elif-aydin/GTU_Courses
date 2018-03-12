import java.util.List;
import java.util.Scanner;

/**
 * Created by elif on 25-Feb-17.
 */
public final class LibraryStaff extends AbstractUser
{
    /**
     * This method is a simple welcome menu for users
     * @return Users choice for library system
     */
    public int menu ()
    {
        System.out.println("\nWhat would you wanna do ?\n");
        System.out.println("1) Register a new user");
        System.out.println("2) Add a new book");
        System.out.println("3) Remove a book");
        System.out.println("4) Exit ");

        Scanner input = new Scanner(System.in);

        int choice = input.nextInt();
        while (choice != 1 && choice != 2 && choice != 3 && choice != 4)
        {
            System.out.println("You have to choose 1, 2, 3 or 4");
            choice = input.nextInt();
        }

        return choice;
    }

    /**
     * This method register a new user on the system
     * @param users User array for searching
     * @return situation of registering
     */
    public boolean registerUser(List<User> users)
    {
        LibraryUser user= new LibraryUser();
        Scanner input = new Scanner(System.in);

        System.out.print("Enter the name of new user: ");
        String name = input.nextLine();
        System.out.print("Enter the surname of new user: ");
        String surname =input.nextLine();
        System.out.print("Enter the ID of new user: ");
        String ID =input.nextLine();
        System.out.print("Give the password for new user: ");
        String password =input.nextLine();

        if(!checkUser(ID,users))
            return false;

        user.setUserName(name);
        user.setUserSurname(surname);
        user.setID(ID);
        user.setPassword(password);
        user.setNumOfBooks(0);

        users.add(user);
        System.out.println("You added the system " + user.getUserName() + " " + user.getUserSurname());
        return true;
    }

    /**
     * This method checks if the given ID is in the system
     * @param ID for checking the user
     * @param users Array for searching users
     * @return Situation of checking
     */
    private boolean checkUser(String ID, List<User> users)
    {
        for (User user : users)
        {
            if(user.getID() == ID)
            {
                System.out.println("You created this person before.");
                return false;
            }
        }
        return true;
    }

    /**
     * This method add new books in the system
     * @param books Books array for searching books to remove
     * @return Situation of the addition
     */
    public boolean addBook(List<Book> books)
    {
        Book book = new Book();
        Scanner input = new Scanner(System.in);

        System.out.print("Enter the name of book to create: ");
        String name = input.nextLine();
        System.out.print("Enter the author of the book: ");
        String author =input.nextLine();
        System.out.print("Enter the ID of book: ");
        String ID = input.nextLine();
        
        boolean result = checkBookID(ID,books);
        while(!result)
        {
            System.out.print("\nGive another ID number for book: ");
            ID = input.nextLine();
            result = checkBookID(ID,books);
        }

        book.setBookName(name);
        book.setAuthor(author);
        book.setOwner("-1"); //Kitap kimsede degil
        book.setID(ID);

        books.add(book);
        System.out.println(name + " added the library system.");
        return true;
    }

    /**
     * This method checks if the given book ID is in the system
     * @param ID ID for checking the book
     * @param books Books array for searching
     * @return true if ID is not present, false if ID is present
     */
    private boolean checkBookID(String ID, List<Book> books)
    {
        for (Book book : books)
        {
            if(book.getID().equals(ID))
            {
                System.out.print("This ID is already given to another book.");
                return false;
            }
        }
        return true;
    }

    /**
     * This method remove books on the system
     * @param books Array to searching books for remove
     * @return situation of removing
     */
    public boolean removeBook(List<Book> books)
    {
        Scanner input = new Scanner(System.in);

        System.out.print("Enter the name of book or ID of the book for remove the system: ");
        String unknown = input.nextLine();
        Book book = checkBookForRemove(unknown,books);
        if(book == null)
        {
            System.out.println("The book not exist in the system");
            return false;
        }
        if(!book.getOwner().equals("-1")) //Kitap kimsede degil
        {
            System.out.println("The book is has an owner. You can't remove it now.");
            return false;
        }
        System.out.println(book.getBookName() + " is removing on the system.");
        books.remove(book);
        return true;
    }

    /**
     * Compares information if the book in the system returns a reference of user. Otherwise returns null
     * @param unknown Unknown variable to check own type
     * @param books Array for searching
     * @return Book reference or null
     */
    private Book checkBookForRemove(String unknown, List<Book> books)
    {
        for (Book book : books)
            if(book.getID().equals(unknown) || book.getBookName().equals(unknown))
                return book;

        return  null;
    }

    /**
     * This method overrided from object class
     * @return library staff information
     */
    @Override
    public String toString()
    {
        return "staff" + "," + super.toString();
    }
}
