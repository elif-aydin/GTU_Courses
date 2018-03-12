import java.util.List;
import java.util.Scanner;

/**
 * Created by elif on 19-Feb-17.
 */

public final class LibraryUser extends AbstractUser
{

    // Max 3 kitap alinabilir
    private int numOfBooks;

    /**
     * Default constructor
     */
    public LibraryUser()
    {
        numOfBooks = 0;
    }

    /**
     * This method is a simple welcome menu for users
     * @return Users choice for library system
     */
    public int menu()
    {
        System.out.println("\nWhat would you wanna do ?\n");
        System.out.println("1) Return a book ");
        System.out.println("2) Borrow a book ");
        System.out.println("3) Show my books ");
        System.out.println("4) Show unowned books ");
        System.out.println("5) Exit ");

        Scanner input = new Scanner(System.in);

        int choice = input.nextInt();
        while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5)
        {
            System.out.println("You have to choose 1, 2 or 3");
            choice = input.nextInt();
        }

        return choice;
    }

    /**
     * This method returns number of books
     * @return Number of books
     */
    public int getNumOfBooks()
    {
        return numOfBooks;
    }

    /**
     * This method sets number of books
     * @param numOfBooks Number of books
     */
    public void setNumOfBooks(int numOfBooks)
    {
        this.numOfBooks = numOfBooks;
    }

    /**
     * This method can help barrow a book for library users
     * @param books Books array for borrowing
     * @return Situation of borrrowing
     */
    public boolean barrow(List<Book> books)
    {
        if (!(numOfBooks < 3))
        {
            System.out.println("You can only have 3 books.");
            return false;
        }

        System.out.print("Enter the name of the book: ");
        Scanner input = new Scanner(System.in);
        String name = input.nextLine();
        Book book = searchBook(name, books);
        if (book == null)
        {
            System.out.println("There is no book named " + name);
            return false;
        }

        if (!book.getOwner().equals("-1")) // kitap birindeyse -1 döner
        {
            System.out.println("This book is already taken.");
            return false;
        }

        book.setOwner(getID());
        numOfBooks++;
        System.out.println("You owned the " + name);

        return true;
    }

    /**
     * This method search books in the given book array
     * @param bookName Book name for searching
     * @param books Array for searching
     * @return search situation
     */
    private Book searchBook(String bookName, List<Book> books)
    {
        for (Book book : books)
        {
            if (book.getBookName().equals(bookName))
                return book;
        }

        return null;
    }

    /**
     * This method for returnin a book to system
     * @param books Array for searching
     * @return situation of returning
     */
    public boolean returnBook(List<Book> books)
    {
        if (!(numOfBooks > 0))
        {
            System.out.println("You don't have any book to return.");
            return false;
        }

        System.out.print("Enter the name of the book to give back: ");
        Scanner input = new Scanner(System.in);
        String name = input.nextLine();
        Book book = searchBook(name, books);
        if (book == null)
        {
            System.out.println("There is no book named " + name);
            return false;
        }
        if(!(getID().equals(book.getOwner())))
        {
            System.out.println("You don't have this book.");
            return false;
        }

        book.setOwner("-1");
        numOfBooks--;
        System.out.println("You returned the " + name);
        return true;
    }

    public void printOwnedBooks(List<Book> books)
    {
        System.out.println("You have these books: ");
        for (Book book : books) 
        {
            if (book.getOwner().equals(getID())) 
            {
                System.out.println(book.getID() + " - " + book.getBookName());
            }
        }
    } 

    /**
     * This method overrided from object class
     * @return library user information
     */
    @Override
    public String toString()
    {
        return "user" + "," + super.toString() + "," + numOfBooks;
    }

}