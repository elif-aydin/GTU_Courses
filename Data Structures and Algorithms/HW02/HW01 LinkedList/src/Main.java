import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by elif on 21-Feb-17.
 */
public class Main {
	final static String lexicon = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	final static String numbers = "0123456789";

	final static  java.util.Random rand = new java.util.Random();


	public static String randomIdentifier(String s) {
		StringBuilder builder = new StringBuilder();
		while(builder.toString().length() == 0) {
			int length = rand.nextInt(5)+5;
			for(int i = 0; i < length; i++) {
				builder.append(s.charAt(rand.nextInt(s.length())));
			}
		}
		return builder.toString();
	}

	public static void main(String[] args)
	{
		long start = System.currentTimeMillis();
		System.out.println("Testing LinkedList with 15000 input.\n");
		LibraryStaff ls = new LibraryStaff();
		List<User> users = new LinkedList<>();

		for (int i = 0; i < 15000; i++) {
			String name = randomIdentifier(lexicon);
			String surname = randomIdentifier(lexicon);
			String id = randomIdentifier(numbers);
			String passWord = randomIdentifier(numbers + lexicon);

			ls.registerTest(name, surname, id, passWord, users);
		}

		long total = System.currentTimeMillis() - start;
		System.out.println("ms: " + total);
		System.out.println("second: " + Math.round(total / 1000L));

	}
}
