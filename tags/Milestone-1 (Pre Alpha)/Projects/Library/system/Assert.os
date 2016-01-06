
public namespace System
{
	public object Assert
	{
		public void assertmsg(string message const, bool condition const) static
		{
			if ( condition == false ) {
				print(message);

				assert(condition);
			}
		}
	}
}
