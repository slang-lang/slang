
// Library imports

// Project imports
import LibLog;


public object StdOutLogger extends Logger {
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
	 * Private members
	 */
	private bool mHasParent const;
}

