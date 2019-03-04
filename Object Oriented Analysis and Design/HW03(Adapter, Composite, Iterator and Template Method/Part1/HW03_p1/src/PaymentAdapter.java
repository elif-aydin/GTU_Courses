/**
 * The adapter class that seems like legacy Turbo, but calls new Modern payment.
 */
public class PaymentAdapter implements TurboPayment{
    private ModernPayment modernPayment;

    public PaymentAdapter() {
        modernPayment = new ModernPaymentImpl();
    }

    @Override
    public int payInTurbo(String turboCardNo, float turboAmount, String destinationTurboOfCourse, String installmentsButInTurbo) {
        return modernPayment.pay(turboCardNo, turboAmount, destinationTurboOfCourse, installmentsButInTurbo);
    }
}
