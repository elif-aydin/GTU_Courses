import java.util.*;

//**************************************
// JPROFİLER icin olustuturulmustur.
//************************************
public class MainQ1
{
    public static void main(String args[]){

        final Boolean q1 = Q1Test();
        if (q1 == Boolean.TRUE)
        {
            System.out.println("Your tests is done. Make sure that you test all methods of class!! " );
            return;
        }
    }

    public static Boolean Q1Test(){

        System.out.println("Q1");
        NavigableMap<String,String> turkey = new BinaryNavMap<String,String>();
        turkey.put("uskudar","istanbul");
        turkey.put("kadıkoy","istanbul");
        turkey.put("cekirge","bursa");
        turkey.put("gebze","kocaeli");
        turkey.put("niksar","tokat");
        turkey.put("kecıoren","ankara");
        turkey.put("aksaray","istanbul");
        turkey.put("foca","izmir");
        turkey.put("manavgat","antalya");
        turkey.put("kahta","adıyaman");
        turkey.put("biga","canakkale");

        System.out.println("The original set odds: " + turkey);
        NavigableMap<String,String> m = turkey.subMap("gebze",true,"uskudar",false);
        System.out.println("The sub map for [gebze, uskudar): " + m);

        System.out.println("The tail set for kahta (exclusive): " + turkey.tailMap("kahta", false));
        System.out.println("The head set for kahta (exclusive): " + turkey.headMap("kahta", false));
        System.out.println("First and last key: " + turkey.firstKey() + " - " + turkey.lastKey());

        System.out.println("lowerKey(gebze): " + turkey.lowerKey("gebze"));
        System.out.println("lowerEntry(gebze): " + turkey.lowerEntry("gebze"));

        System.out.println("floorKey(gebze): " + turkey.floorKey("gebze"));
        System.out.println("floorEntry(gebze): " + turkey.floorEntry("gebze"));

        System.out.println("ceilingKey(gebze): " + turkey.ceilingKey("gebze"));
        System.out.println("ceilingEntry(gebze): " + turkey.ceilingEntry("gebze"));

        System.out.println("higherKey(gebze): " + turkey.higherKey("gebze"));
        System.out.println("higherEntry(gebze): " + turkey.higherEntry("gebze"));

        System.out.println("The first entry: " +turkey.firstEntry());
        System.out.println("The last entry: " +turkey.lastEntry());
        turkey.pollFirstEntry();
        System.out.println("pollFirstEntry called: " + turkey);
        turkey.pollLastEntry();
        System.out.println("pollLastEntry called: " + turkey);

        turkey.put("gebze", "owww");
        System.out.println("put(\"gebze\", \"owww\") called: " + turkey);

        turkey.put("battalgazi", "malatya");
        System.out.println("put(\"battalgazi\", \"malatya\") called: " + turkey);

        System.out.println("\n");
        return Boolean.TRUE;
    }
}
