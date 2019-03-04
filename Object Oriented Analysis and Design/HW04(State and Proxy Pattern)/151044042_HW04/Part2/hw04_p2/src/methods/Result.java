package methods;

import java.io.Serializable;

/**
 * Class to represent results of service.
 */
public class Result implements Serializable {

	private String resultStr;
	private String error;

	/**
	 * Constructs result with result and errors.
	 * @param resultStr
	 * @param error
	 */
	public Result (String resultStr, String error) {
		this.resultStr = resultStr;
		this. error = error;
	}

	/**
	 * Constructs result from another Result object.
	 * @param result
	 */
	public Result(Result result) {
		this.resultStr = result.getResultStr();
		this.error = result.getError();
	}

	/**
	 * Getter for result.
	 * @return result
	 */
	public String getResultStr() {
		return resultStr;
	}

	/**
	 * Setter for result.
	 * @param resultStr
	 */
	public void setResultStr(String resultStr) {
		this.resultStr = resultStr;
	}

	/**
	 * Getter for errors.
	 * @return error
	 */
	public String getError() {
		return error;
	}

	/**
	 * Setter for errors.
	 * @param error
	 */
	public void setError(String error) {
		this.error = error;
	}

}