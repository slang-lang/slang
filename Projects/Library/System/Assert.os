
public namespace System
{
	public void assertmsg(string message, bool condition)
	{
		if ( !condition ) {
			write(message + ": ");

			assert(condition);
		}
	}
}
