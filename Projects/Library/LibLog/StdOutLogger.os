
// Library imports

// Project imports
import Context;
import ILogger;


public object StdOutLogger const implements ILogger {
	// Members
	private IContext mContext const;
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

	public IContext getContext() const {
		return mContext;
	}

	public string getKey() const {
		return mKey;
	}

	// Public methods
	public void debug(string message) {
		print("[DEBUG] [" + mKey + "]   " + message);
	}

	public void error(string message) {
		print("[ERROR] [" + mKey + "]   " + message);
	}

	public void fatal(string message) {
		print("[FATAL] [" + mKey + "]   " + message);

		exit(-1);
	}

	public void info(string message) {
		print("[INFO ] [" + mKey + "]   " + message);
	}

	public void warning(string message) {
		print("[WARN ] [" + mKey + "]   " + message);
	}

	public string =operator(string none) const {
		return mKey;
	}
}

