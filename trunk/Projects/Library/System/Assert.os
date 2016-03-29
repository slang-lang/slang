
public namespace System
{
	public void assertmsg(string message, bool condition)
	{
		if ( !condition ) {
			write(message + ": ");

			assert(condition);
		}
	}

	public void debug(bool condition, string msg_success, string msg_fail)
	{
		if ( condition ) {
			print(msg_success);
		}
		else {
			print(msg_fail);
		}
	}
}
