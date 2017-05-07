
public object StdOutLogger const {
	// Members
	private string mKey final;

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
	 * Default destructor
	 */
	public void Destructor() {
		// nothing to do here
	}

	// Public methods
	public void debug(string message) {
		print("[DEBUG] " + mKey + "::" + message);
	}

	public void error(string message) {
		print("[ERROR] " + mKey + "::" + message);
	}

	public void info(string message) {
		print("[INFO ] " + mKey + "::" + message);
	}

	public void warning(string message) {
		print("[WARN ] " + mKey + "::" + message);
	}
}

