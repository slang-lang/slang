
// Library imports

// Project imports
import LibLog;


public object StdOutLogger implements ILogger {
	// Members
	private IContext mContext;
	private bool mHasParent const;
	private string mKey const;
	private int mKeyLength const;

	/*
	 * Specialised constructor
	 */
	public void Constructor(string key, int keyLength = 0) {
		mContext = IContext new StdOutContext();
		mKeyLength = keyLength;

		if ( keyLength && strlen(key) > keyLength ) {
			mKey = substr(key, strlen(key) - keyLength, keyLength);
		}
		else {
			mKey = key;
		}
	}

	/*
	 * Copy constructor
	 */
	public void Constructor(ILogger parent ref, string key, int keyLength) throws {
		if ( !parent ) {
			throw new Exception("missing parent logger");
		}

		mContext = parent.getContext();
		mHasParent = true;
		mKeyLength = keyLength;

		mKey = parent.getKey() + LibLog.KeySeparator + key;

		if ( keyLength && strlen(mKey) > keyLength ) {
			mKey = substr(mKey, strlen(mKey) - keyLength, keyLength);
		}
	}

	/*
	 * Default destructor
	 */
	public void Destructor() {
	}

	public IContext getContext() const {
		return mContext;
	}

	public string getKey() const {
		return mKey;
	}

	public int getKeyLength() const {
		return mKeyLength;
	}

	// Public methods
	public void debug(string message) modify {
		mContext.write("[DEBUG] [" + mKey + "]   " + message);
	}

	public void error(string message) modify {
		mContext.write("[ERROR] [" + mKey + "]   " + message);
	}

	public void fatal(string message) modify throws {
		mContext.write("[FATAL] [" + mKey + "]   " + message);

        throw new FatalError(message);
	}

	public void info(string message) modify {
		mContext.write("[INFO ] [" + mKey + "]   " + message);
	}

	public void warning(string message) modify {
		mContext.write("[WARN ] [" + mKey + "]   " + message);
	}
}
