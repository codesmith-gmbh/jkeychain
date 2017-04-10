package pt.davidafsilva.apple;

/** Auto-generated from Security.h, see the Keychain Services Reference for
 *	descriptions of what these constants mean.
 */
public enum OSXKeychainAuthenticationType {
	/** kSecAuthenticationTypeAny */
	Any("Any", 0),

	/** kSecAuthenticationTypeDPA */
	DPA("DPA", 1633775716),

	/** kSecAuthenticationTypeDefault */
	Default("Default", 1953261156),

	/** kSecAuthenticationTypeHTMLForm */
	HTMLForm("HTMLForm", 1836216166),

	/** kSecAuthenticationTypeHTTPBasic */
	HTTPBasic("HTTPBasic", 1886680168),

	/** kSecAuthenticationTypeHTTPDigest */
	HTTPDigest("HTTPDigest", 1685353576),

	/** kSecAuthenticationTypeMSN */
	MSN("MSN", 1634628461),

	/** kSecAuthenticationTypeNTLM */
	NTLM("NTLM", 1835824238),

	/** kSecAuthenticationTypeRPA */
	RPA("RPA", 1633775730);

	/** The name of the constant. */
	private final String symbol;

	/** The value of the constant. */
	private final int value;

	/** Create the constant. 
	 *
	 *	@param sym The name of the constant.
	 *	@param val The value of the constant.
	 */
	OSXKeychainAuthenticationType(String sym, int val) {
		symbol = sym;
		value = val;
	}

	/** Get the value of the constant.
	 *
	 *	@return	The value of the constant.
	 */
	public int getValue() {
		return value;
	}

	/** {@inheritDoc} */
	@Override
	public String toString() {
		return symbol;
	}
}
