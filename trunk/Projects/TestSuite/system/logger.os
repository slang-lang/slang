
public namespace System
{
	public object Logger
	{
		// Members
		private string mKey;
		
		// Default constructor
		public void Logger()
		{
			mKey = "Logger";
		}

		// Specialized constructor
		public void Logger(string key)
		{
			mKey = key;
		}

		// Public methods
		public void debug(string message) const
		{
			print("[OS::DEBUG] " & mKey & "::" & message);
		}

		public void error(string message) const
		{
			print("[OS::ERROR] " & mKey & "::" & message);
		}

		public void info(string message) const
		{
			print("[OS::INFO ] " & mKey & "::" & message);
		}

		public void warning(string message) const
		{
			print("[OS::WARN ] " & mKey & "::" & message);
		}
	}
}
