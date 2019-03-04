/**
 * Implementation of the new Modern Payment API.
 */
public class ModernPaymentImpl implements ModernPayment {
    @Override
    public int pay(String cardNo, float amount, String destination, String installments) {
        System.out.println("Modern Payment completed successfully.");
        return 0;
    }
}
