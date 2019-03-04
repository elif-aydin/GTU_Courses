public class Main {
    public static void main(String[] args) {
        PaymentAdapter adapter = new PaymentAdapter();

        System.out.println("Paying with adapter (must call modern API internally): ");
        adapter.payInTurbo("123456", 788, "654321", "3 4 55");
    }
}
