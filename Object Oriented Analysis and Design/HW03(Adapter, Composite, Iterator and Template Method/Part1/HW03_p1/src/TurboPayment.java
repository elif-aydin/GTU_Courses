/**
 * Legacy payment API.
 */
public interface TurboPayment {
    int payInTurbo(String turboCardNo, float turboAmount,
                   String destinationTurboOfCourse, String installmentsButInTurbo);
}
