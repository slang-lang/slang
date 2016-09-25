
public namespace System {
public namespace IO {

	public object Logger {
		// Members
		private string mKey final;

		// Specialised constructor
		public void Logger(string key, int keyLength = 0) {
			if ( keyLength ) {
				mKey = substr(key, strlen(key) - keyLength, keyLength);
			}
			else {
				mKey = key;
			}
		}

		// Public methods
		public void debug(string message) {
			writeln("[DEBUG] " + mKey + "::" + message);
		}

		public void error(string message) {
			writeln("[ERROR] " + mKey + "::" + message);
		}

		public void info(string message) {
			writeln("[INFO ] " + mKey + "::" + message);
		}

		public void warning(string message) {
			writeln("[WARN ] " + mKey + "::" + message);
		}
	}

}
}

