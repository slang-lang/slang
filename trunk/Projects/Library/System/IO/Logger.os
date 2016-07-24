
public namespace System {
public namespace IO {

	public object Logger {
		// Members
		private string mKey final;

		// Specialised constructor
		public void Logger(string key const, int keyLength = 0) {
			if ( keyLength ) {
				mKey = substr(key, strlen(key) - keyLength, keyLength);
			}
			else {
				mKey = key;
			}
		}

		// Public methods
		public void debug(string message const) {
			writeln("[DEBUG] " + mKey + "::" + message);
		}

		public void error(string message const) {
			writeln("[ERROR] " + mKey + "::" + message);
		}

		public void info(string message const) {
			writeln("[INFO ] " + mKey + "::" + message);
		}

		public void warn(string message const) {
			writeln("[WARN ] " + mKey + "::" + message);
		}
	}

}
}

