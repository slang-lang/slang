
// Library imports

// Project imports
import Context;

public object FileLogger {
	// Members
	private FileContext mContext;
	private string mKey const;

	/*
	 * Specialised constructor
	 */
	public void Constructor(FileContext context, string key, int keyLength = 0) {
		if ( keyLength ) {
			mKey = substr(key, strlen(key) - keyLength, keyLength);
		}
		else {
			mKey = key;
		}

		if ( context ) {
			mContext = context;
		}
		else {
			mContext = new FileContext();
		}
	}

	// Public methods
	public void debug(string message) {
		mContext.write("[DEBUG] " + mKey + "::" + message);
	}

	public void error(string message) {
		mContext.write("[ERROR] " + mKey + "::" + message);
	}

	public void info(string message) {
		mContext.write("[INFO ] " + mKey + "::" + message);
	}

	public void warning(string message) {
		mContext.write("[WARN ] " + mKey + "::" + message);
	}
}

