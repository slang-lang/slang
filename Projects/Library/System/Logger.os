
public namespace System
{
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
			print("[OS::DEBUG] " & mKey & "::" & message);
		}

		public void error(string message const)
		{
			print("[OS::ERROR] " & mKey & "::" & message);
		}

		public void info(string message const)
		{
			print("[OS::INFO ] " & mKey & "::" & message);
		}

		public void warning(string message const)
		{
			print("[OS::WARN ] " & mKey & "::" & message);
		}

	}
}
