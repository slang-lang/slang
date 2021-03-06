
// Library imports

// Project imports
import LibLog;


public object Logger implements ILogger {
	/*
	 * Default constructor
	 * expects a parent logger and a key, uses parent's keylength
	 */
	public void Constructor(ILogger parent, string key) throws {
		if ( !parent ) {
			throw new Exception("missing parent logger");
		}

		mContext = parent.getContext();
		mKey = strrtrim(parent.getKey()) + LibLog.KeySeparator + key;
		mKeyLength = parent.getKeyLength();

		if ( mKeyLength ) {
			if ( strlen(mKey) > mKeyLength ) {
				mKey = substr(mKey, strlen(mKey) - mKeyLength, mKeyLength);
			}

			mKey = strrpad(mKey, mKeyLength, " ");
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

		throw new FatalError("fatal error: " + message);
	}

	public void info(string message) modify {
		mContext.write("[INFO ] [" + mKey + "]   " + message);
	}

	public void warning(string message) modify {
		mContext.write("[WARN ] [" + mKey + "]   " + message);
	}

	/*
	 * Protected members
	 */
	protected IContext mContext const;
	protected string mKey const;
	protected int mKeyLength const;
}

