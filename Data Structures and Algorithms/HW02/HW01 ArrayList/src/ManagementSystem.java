import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * Created by elif on 21-Feb-17.
 */
public final class ManagementSystem
{
    private List<Book> books;
    private List<User> users;
    private final String booksCsv = "src/books.csv";
    private final String usersCsv = "src/users.csv";
    private final String splitter = ","; //Csv dosyasini ayirmak icin

    /**
     * Default constructor
     */
    public ManagementSystem() throws Exception
    {
        books = new ArrayList<>();
        users = new ArrayList<>();

        readBooks();
        readUsers();
    }

    /**
     * This method run all the library system
     */
    public void run()
    {
        User currentUser = login();
        if (currentUser == null) //User login islemi basarisiz olursa
            return;

        boolean flag = true; // Secimleri kontrol etmek ve donguyu kontrol etmek icin
        while (flag)
        {
            int choice = currentUser.menu(); //Kullanicinin yapmak istedigi islem belirlenir
            if (currentUser instanceof LibraryUser)  // Hangi user tipi oldugu kiyaslamasi yapilir
            {
                LibraryUser lUser = (LibraryUser) currentUser;
                if (choice == 1) //Return a book
                    lUser.returnBook(books);
                else if (choice == 2) //Borrow a book
                    lUser.barrow(books);
                else if (choice == 3) // Show my books
                    lUser.printOwnedBooks(books);
                else if (choice == 4)
                    printFreeBooks();
                else if (choice == 5) // Cikis yapmak icin
                    flag = false; //Exit yapmak icin kullanilir
            }
            else //Library user degilse library staff dir
            {
                // call staff methods
                LibraryStaff lStaff = (LibraryStaff) currentUser;
                if (choice == 1)
                    lStaff.registerUser(users);
                else if (choice == 2)
                    lStaff.addBook(books);
                else if (choice == 3)
                    lStaff.removeBook(books);
                else if (choice == 4)
                    flag = false; //Exit yapmak icin kullanilir
            }
        }

        // Yapilan degisikleri dosyamıza kaydederiz.
        try
        {
            FileWriter bookWriter = new FileWriter(booksCsv);
            for (Book book : books)
                bookWriter.write(book.toString() + "\n");
            bookWriter.close();

            FileWriter userWriter = new FileWriter(usersCsv);
            for (User user : users)
                userWriter.write(user.toString() + "\n");
            userWriter.close();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }

        System.out.println("Goodbye.");
    }

    private void printFreeBooks()
    {
        System.out.println("These are the unclaimed books: ");
        for (Book book : books) 
        {
            if (book.getOwner().equals("-1")) 
            {
                System.out.println(book.getID() + " - " + book.getBookName());        
            }    
        }
    }

    /**
     * This method reads books.csv to array an split it
     * @throws Exception if file is not present
     */
    private void readBooks() throws Exception
    {
        String line; // Dosyayi okuyacagimiz string
        //Reading book file
        try (BufferedReader br = new BufferedReader(new FileReader(booksCsv)))
        {
            while ((line = br.readLine()) != null)
            {
                String[] arr = line.split(splitter);

                Book book = new Book();
                book.setBookName(arr[0]);
                book.setAuthor(arr[1]);
                book.setID(arr[2]); //Book ID
                book.setOwner(arr[3]); // Book owner(user) ID

                books.add(book);
            }
        }
        catch (IOException e)
        {
            System.err.println("books.csv is missing.");
            throw e;
        }
    }

    /**
     * This method reads user.csv to array an split it
     * @throws Exception if file is not present
     */
    private void readUsers() throws Exception
    {
        String line;

        //Reading user file
        try (BufferedReader br = new BufferedReader(new FileReader(usersCsv)))
        {
            while ((line = br.readLine()) != null)
            {
                String[] arr = line.split(splitter); // stringi verdiğin karaktere göre parçalayıp, her bir parçayı arraye kaydedip arrayi return eder.

                if (arr[0].equals("user"))
                {
                    LibraryUser user = new LibraryUser();
                    user.setUserName(arr[1]);
                    user.setUserSurname(arr[2]);
                    user.setID(arr[3]);
                    user.setPassword(arr[4]);
                    user.setNumOfBooks(Integer.parseInt(arr[5]));

                    users.add(user);
                }
                else
                {
                    LibraryStaff user = new LibraryStaff();
                    user.setUserName(arr[1]);
                    user.setUserSurname(arr[2]);
                    user.setID(arr[3]);
                    user.setPassword(arr[4]);

                    users.add(user);
                }
            }
        }
        catch (IOException e)
        {
            System.err.println("users.csv is missing.");
            throw e;
        }
    }

    /**
     * Compares information and if the user in the system returns a reference of user. Otherwise returns null
     * @return reference of user or null
     */
    public User login()
    {
        System.out.println("Welcome to system");
        System.out.print("Enter your ID: ");
        Scanner input = new Scanner(System.in);
        String ID = input.next();

        int idResult = searchID(ID); //ID bulunamazsa -1 doner

        if(idResult != -1)
        {
            System.out.print("Enter your password: ");
            String password = input.next();

            if(users.get(idResult).getPassword().equals(password))
            {
                return users.get(idResult);
            }
            else
            {
                System.out.println("You entered a wrong password"); //Kullaniciya sifre girme hakki 1 kere verilir
                return null;
            }
        }
        System.out.println("You are not registered the system before.");
        return null;
    }

    /**
     * This method check the given ID and return the user's index
     * @param ID ID for search
     * @return the user's index of given ID
     */
    private int searchID(String ID)
    {
        for (int i = 0; i < users.size(); i++)
        {
            //Yazdigimiz csv de 2. eleman ID dir. Get bize string array i getiriyo. Biz o string array inin 2 sine bakariz
            if(users.get(i).getID().equals(ID))
                return i;
        }
        return -1;
    }
}