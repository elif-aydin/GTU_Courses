/**
 * Created by elif on 19-Feb-17.
 */
public final class Book
{
    private String bookName;
    private String author;
    private String owner;
    private String ID;

    /**
     * Default constructor
     */
    public Book()
    {
        bookName = null;
        author = null;
        owner = "-1"; // kimse kitaba sahip değil
        ID = null;
    }

    /**
     * Book Constructor
     * @param bookName Book name for initialize
     * @param author Author for initialize
     * @param owner Book situation
     * @param ID Book ID
     */
    public Book(String bookName, String author, String owner,String ID)
    {
        this.bookName = bookName;
        this.author = author;
        this.owner = owner;
        this.ID = ID;
    }

    /**
     * Copy constructor for book
     * @param book Object to copy
     */
    public Book(Book book)
    {
        bookName = book.getBookName();
        author = book.getAuthor();
        owner = book.getOwner();
        ID = book.getID();
    }

    /**
     * This method return book's name
     * @return Book name
     */
    public String getBookName()
    {
        return bookName;
    }

    /**
     * This method set book's name
     * @param bookName Name of the book
     */
    public void setBookName(String bookName)
    {
        this.bookName = bookName;
    }

    /**
     * This method return author's name
     * @return Author's name
     */
    public String getAuthor()
    {
        return author;
    }

    /**
     * This method set author's name
     * @param author Author's name
     */
    public void setAuthor(String author)
    {
        this.author = author;
    }

    /**
     * This method get book situation
     * @return situation
     */
    public String getOwner()
    {
        return owner;
    }

    /**
     * This method set book situation
     * @param owner Situation of book
     */
    public void setOwner(String owner)
    {
        this.owner = owner;
    }

    /**
     * This method get book ID
     * @return Book Id
     */
    public String getID()
    {
        return ID;
    }

    /**
     * This method set book ID
     * @param ID ID of book
     */
    public void setID(String ID)
    {
        this.ID = ID;
    }

    /**
     * This method overrided from object class
     * @return Information of book
     */
    @Override
    public String toString()
    {
        String newString;
        newString = bookName + "," + author + "," + ID +  "," + owner;
        return newString;
    }
}