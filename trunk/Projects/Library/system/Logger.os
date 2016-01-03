
public namespace System
{
	public object Logger
	{
		// Members
		private string mKey;

		// specialized constructor
		public void Logger(string key)
		{
			mKey = key;
		}

		// Public methods
		public void debug(string message)
		{
			print("[OS::DEBUG] " + mKey + "::" + message);
		}

		public void error(string message)
		{
			print("[OS::ERROR] " + mKey + "::" + message);
		}

		public void info(string message)
		{
			print("[OS::INFO ] " + mKey + "::" + message);
		}

		public void warning(string message)
		{
			print("[OS::WARN ] " + mKey + "::" + message);
		}

	}
}
