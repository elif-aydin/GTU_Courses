package methods;

/**
 * A result representation of server calls that includes caller's apikey and remaining balance.
 */
public class ServiceResult extends Result {
    private String apiKey;
    private Integer remainingBalance;

    /**
     * Construct this Result with result, error, apikey and remaining balance.
     * @param resultStr
     * @param error
     * @param apiKey
     * @param remainingBalance
     */
    public ServiceResult(String resultStr, String error, String apiKey, Integer remainingBalance) {
        super(resultStr, error);
        this.apiKey = apiKey;
        this.remainingBalance = remainingBalance;
    }

    /**
     * Construct this Result with given Result with addition to apikey and remaining balance.
     * @param result
     * @param apiKey
     * @param remainingBalance
     */
    public ServiceResult(Result result, String apiKey, Integer remainingBalance) {
        super(result);
        this.apiKey = apiKey;
        this.remainingBalance = remainingBalance;
    }

    /**
     * Getter for apikey.
     * @return apiKey
     */
    public String getApiKey() {
        return apiKey;
    }

    /**
     * Getter for remaining balance.
     * @return remainingBalance
     */
    public Integer getRemainingBalance() {
        return remainingBalance;
    }
}
