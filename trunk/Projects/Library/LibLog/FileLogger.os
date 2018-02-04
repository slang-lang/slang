
// Library imports

// Project imports
import Context;
import ILogger;


public object FileLogger const implements ILogger {
	// Members
	private IContext mContext;
	private bool mHasParent const;
	private string mKey const;

	/*
	 * Specialised constructor
	 */
	public void Constructor(string key, int keyLength = 0) {
		if ( keyLength ) {
			mKey = substr(key, strlen(key) - keyLength, keyLength);
		}
		else {
			mKey = key;
		}

		mContext = IContext new FileContext();
	}

	/*
	 * Copy constructor
	 */
	public void Constructor(ILogger parent ref, string key, int keyLength = 0) {
		if ( parent ) {
			mContext = parent.getContext();
			mHasParent = true;
			if ( parent.getKey() ) {
				mKey = parent.getKey() + "::";
			}
		}

		mKey += key;

		if ( keyLength && strlen(mKey) > keyLength ) {
			mKey = substr(mKey, strlen(mKey) - keyLength, keyLength);
		}

		if ( !mContext ) {
			mContext = IContext new StdOutContext();
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

