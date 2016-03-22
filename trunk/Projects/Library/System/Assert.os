
public namespace System
{
	public void assertmsg(string message const, bool condition)
	{
		if ( !condition ) {
			print(message);

			assert(condition);
		}
	}
}
