
// Library imports

// Project imports
import LibLog;


public object StdOutLogger implements ILogger {
	/*
	 * Specialised constructor
	 */
	public void Constructor(string key, int keyLength = 0) {
		mContext = IContext new StdOutContext();
		mKey = key;
		mKeyLength = keyLength;

		if ( mKeyLength ) {
			if ( strlen(mKey) > mKeyLength ) {
				mKey = substr(mKey, strlen(mKey) - mKeyLength, mKeyLength);
			}

			mKey = strrpad(mKey, mKeyLength, " ");
		}
	}

	/*
	 * Copy constructor
	 */
	public void Constructor(ILogger parent, string key) throws {
		if ( !parent ) {
			throw new Exception("missing parent logger");
		}

		mContext = parent.getContext();
		mHasParent = true;
		mKey = parent.getKey() + LibLog.KeySeparator + key;
		mKeyLength = parent.getKeyLength();

		if ( mKeyLength ) {
			if ( strlen(mKey) > mKeyLength ) {
				mKey = substr(mKey, strlen(mKey) - mKeyLength, mKeyLength);
			}

			mKey = strrpad(mKey, mKeyLength, " ");
		}
	}

	/*
	 * Default destructor
	 */
	public void Destructor() {
		if ( !mHasParent ) {
			delete mContext;
		}
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

	/*
	 * Private members
	 */
	private IContext mContext;
	private bool mHasParent const;
	private string mKey const;
	private int mKeyLength const;
}

