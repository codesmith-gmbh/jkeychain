package pt.davidafsilva.apple;

/** Auto-generated from Security.h, see the Keychain Services Reference for
 *	descriptions of what these constants mean.
 */
public enum OSXKeychainProtocolType {
	/** kSecProtocolTypeAFP */
	AFP("AFP", 1634103328),

	/** kSecProtocolTypeAny */
	Any("Any", 0),

	/** kSecProtocolTypeAppleTalk */
	AppleTalk("AppleTalk", 1635019883),

	/** kSecProtocolTypeCIFS */
	CIFS("CIFS", 1667851891),

	/** kSecProtocolTypeCVSpserver */
	CVSpserver("CVSpserver", 1668707184),

	/** kSecProtocolTypeDAAP */
	DAAP("DAAP", 1684103536),

	/** kSecProtocolTypeEPPC */
	EPPC("EPPC", 1701867619),

	/** kSecProtocolTypeFTP */
	FTP("FTP", 1718906912),

	/** kSecProtocolTypeFTPAccount */
	FTPAccount("FTPAccount", 1718906977),

	/** kSecProtocolTypeFTPProxy */
	FTPProxy("FTPProxy", 1718907000),

	/** kSecProtocolTypeFTPS */
	FTPS("FTPS", 1718906995),

	/** kSecProtocolTypeHTTP */
	HTTP("HTTP", 1752462448),

	/** kSecProtocolTypeHTTPProxy */
	HTTPProxy("HTTPProxy", 1752461432),

	/** kSecProtocolTypeHTTPS */
	HTTPS("HTTPS", 1752461427),

	/** kSecProtocolTypeHTTPSProxy */
	HTTPSProxy("HTTPSProxy", 1752462200),

	/** kSecProtocolTypeIMAP */
	IMAP("IMAP", 1768776048),

	/** kSecProtocolTypeIMAPS */
	IMAPS("IMAPS", 1768779891),

	/** kSecProtocolTypeIPP */
	IPP("IPP", 1768976416),

	/** kSecProtocolTypeIRC */
	IRC("IRC", 1769104160),

	/** kSecProtocolTypeIRCS */
	IRCS("IRCS", 1769104243),

	/** kSecProtocolTypeLDAP */
	LDAP("LDAP", 1818517872),

	/** kSecProtocolTypeLDAPS */
	LDAPS("LDAPS", 1818521715),

	/** kSecProtocolTypeNNTP */
	NNTP("NNTP", 1852732528),

	/** kSecProtocolTypeNNTPS */
	NNTPS("NNTPS", 1853124723),

	/** kSecProtocolTypePOP3 */
	POP3("POP3", 1886351411),

	/** kSecProtocolTypePOP3S */
	POP3S("POP3S", 1886351475),

	/** kSecProtocolTypeRTSP */
	RTSP("RTSP", 1920234352),

	/** kSecProtocolTypeRTSPProxy */
	RTSPProxy("RTSPProxy", 1920234360),

	/** kSecProtocolTypeSMB */
	SMB("SMB", 1936548384),

	/** kSecProtocolTypeSMTP */
	SMTP("SMTP", 1936553072),

	/** kSecProtocolTypeSOCKS */
	SOCKS("SOCKS", 1936685088),

	/** kSecProtocolTypeSSH */
	SSH("SSH", 1936943136),

	/** kSecProtocolTypeSVN */
	SVN("SVN", 1937141280),

	/** kSecProtocolTypeTelnet */
	Telnet("Telnet", 1952803950),

	/** kSecProtocolTypeTelnetS */
	TelnetS("TelnetS", 1952803955);

	/** The name of the constant. */
	private final String symbol;

	/** The value of the constant. */
	private final int value;

	/** Create the constant. 
	 *
	 *	@param sym The name of the constant.
	 *	@param val The value of the constant.
	 */
	OSXKeychainProtocolType(String sym, int val) {
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
