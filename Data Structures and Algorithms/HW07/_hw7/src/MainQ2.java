import java.util.*;

//**************************************
// JPROFİLER icin olustuturulmustur.
//************************************

public class MainQ2
{
    public static void main(String args[]){

        final Boolean q2 = Q2Test();
        if (q2 == Boolean.TRUE)
        {
            System.out.println("Your tests is done. Make sure that you test all methods of class!! " );
            return;
        }
    }

    public static Boolean Q2Test()
    {
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
