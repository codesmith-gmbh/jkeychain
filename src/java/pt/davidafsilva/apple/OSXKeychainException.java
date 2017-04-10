package pt.davidafsilva.apple;

/**
 * An exception to be thrown if the native code interacting with the keychain
 * encounters an error.
 *
 * @author Conor McDermottroe
 */
public class OSXKeychainException extends Exception {

  /**
   * Create a blank exception with no message.
   */
  public OSXKeychainException() {
    super();
  }

  /**
   * Create an exception with a message.
   *
   * @param message A message explaining why this exception must be thrown.
   */
  public OSXKeychainException(String message) {
    super(message);
  }

  /**
   * Create an exception with no message but with a link to the exception
   * which caused this one to be thrown.
   *
   * @param cause The reason this exception is being created and thrown.
   */
  public OSXKeychainException(Throwable cause) {
    super(cause);
  }

  /**
   * Create an exception both with a message and a link to the exceptino
   * which caused this one to be thrown.
   *
   * @param message A message explaining why this exception must be thrown.
   * @param cause   The reason this exception is being created and thrown.
   */
  public OSXKeychainException(String message, Throwable cause) {
    super(message, cause);
  }
}
