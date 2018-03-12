import java.util.*;


public class Main
{
    public static void main(String args[]){

        final Boolean q1 = Q1Test();
        final Boolean q2 = Q2Test();
        if (q1 == q2 == Boolean.TRUE)
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

    public static Boolean Q2Test(){
        System.out.println("Q2");

        HashTableChaining<String,String> turkey = new HashTableChaining<String,String>();
        turkey.put("edremit","balikesir");
        turkey.put("edremit","van");
        turkey.put("kemalpasa","bursa");
        turkey.put("kemalpasa","izmir");
        turkey.put("ortakoy","istanbul");//we assume a district
        turkey.put("ortakoy","aksaray");
        turkey.put("ortakoy","corum");
        turkey.put("kecioren","ankara");
        turkey.put("pinarbasi","kastamonu");
        turkey.put("pinarbasi","kayseri");
        turkey.put("eregli","konya");
        turkey.put("eregli","tekirdag");
        turkey.put("eregli","zonguldak");
        turkey.put("golbasi","adıyaman");
        turkey.put("golbasi","ankara");
        turkey.put("biga","canakkale");

        String returnVal;
        System.out.println("Initial map:");
        System.out.println(turkey.getElementsAsString());

        System.out.println("get(\"kecioren\") called: " + turkey.get("kecioren") + "\n");

        returnVal = turkey.put("hekimhan", "kars");
        System.out.println("New state after put(\"hekimhan\", \"kars\") called (return value = " + returnVal + "):");
        System.out.println(turkey.getElementsAsString());

        returnVal = turkey.put("hekimhan", "malatya");
        System.out.println("New state after put(\"hekimhan\", \"malatya\") called (return value = " + returnVal + "):");
        System.out.println(turkey.getElementsAsString());

        returnVal = turkey.remove("hekimhan");
        System.out.println("New state after remove(\"hekimhan\") called: (return value = " + returnVal + "):");
        System.out.println(turkey.getElementsAsString());

        System.out.println("Note: these results are sorted while printing so that you can see easily.");

        System.out.println("\n");
        return Boolean.TRUE;
    }


}
