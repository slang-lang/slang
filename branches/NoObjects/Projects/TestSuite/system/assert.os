
public namespace
{
	public object Assert
	{
		public void assertmsg(String message const, Bool condition const) static
		{
			if ( condition == false ) {
				print(message);

				assert(condition);
			}
		}

		public void debug(Bool condition const, String message const) static
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
