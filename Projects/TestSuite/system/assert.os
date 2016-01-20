
public namespace System
{
	public object Assert
	{
		public void assertmsg(string message, bool condition) const
		{
			if ( !condition ) {
				print(message);
				assert(condition);
			}
		}

		public void debug(bool condition, string message) const
		{
			if ( condition ) {
				print("success: " & message);
			}
			else {
				print("failed: " & message);
			}
		}
	}
}
