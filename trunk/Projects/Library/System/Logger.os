
public namespace System {

	public object Logger
	{
		// Members
		private string mKey final;

		// Specialised constructor
		public void Logger(string key const)
		{
			mKey = key;
		}

		// Public methods
		public void debug(string message const)
		{
			print("[DEBUG] " + mKey + "::" + message);
		}

		public void error(string message const)
		{
			print("[ERROR] " + mKey + "::" + message);
		}

		public void info(string message const)
		{
			print("[INFO ] " + mKey + "::" + message);
		}

		public void warning(string message const)
		{
			print("[WARN ] " + mKey + "::" + message);
		}

	}

}

