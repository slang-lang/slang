
public namespace std
{

	public object Logger
	{
		// Members
		private String mKey;
		
		// Default constructor
		public void Logger()
		{
			mKey = "Logger";
		}

		// Specialized constructor
		public void Logger(String key)
		{
			mKey = key;
		}

		// Public methods
		public void debug(String message)
		{
			print("[OS::DEBUG] " & mKey & "::" & message);
		}

		public void error(String message)
		{
			print("[OS::ERROR] " & mKey & "::" & message);
		}

		public void info(String message)
		{
			print("[OS::INFO ] " & mKey & "::" & message);
		}

		public void warning(String message)
		{
			print("[OS::WARN ] " & mKey & "::" & message);
		}
	}

}