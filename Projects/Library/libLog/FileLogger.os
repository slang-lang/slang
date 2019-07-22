
// Library imports

// Project imports
import LibLog;


public object FileLogger extends Logger {
	/*
	 * Specialised constructor
	 */
	public void Constructor(string filename, string key, int keyLength = 0) {
		mContext = IContext new FileContext(filename);
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
		base.Constructor(parent, key);

		mHasParent = true;
	}

	/*
	 * Default destructor
	 */
	public void Destructor() {
		if ( !mHasParent ) {
			delete mContext;
		}
	}

	/*
	 * Protected members
	 */
	protected bool mHasParent const;
}

public object AppendingFileLogger extends FileLogger {
	/*
	 * Specialised constructor
	 */
	public void Constructor(string filename, string key, int keyLength = 0) {
		mContext = IContext new FileContext(filename, true);
		mKey = key;
		mKeyLength = keyLength;

		if ( mKeyLength ) {
			if ( strlen(mKey) > mKeyLength ) {
				mKey = substr(mKey, strlen(mKey) - mKeyLength, mKeyLength);
			}

			mKey = strrpad(mKey, mKeyLength, " ");
		}
	}
}

