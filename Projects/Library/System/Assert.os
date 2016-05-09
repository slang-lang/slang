
public namespace System {

	public void assert(bool condition, string message)
	{
		if ( !condition ) {
			writeln("failed with message \"" + message + "\"");

			assert(condition);
		}
	}

	public void debug(bool condition, string msg_success, string msg_fail)
	{
		if ( condition ) {
			writeln(msg_success);
		}
		else {
			writeln("[DEBUG] " + msg_fail);
		}
	}

	public void error(bool condition, string msg_success, string msg_fail) {
		if ( condition ) {
			writeln(msg_success);
		}
		else {
			writeln("[ERROR] " + msg_fail);
		}
	}

	public void warn(bool condition, string msg_success, string msg_fail) {
		if ( condition ) {
			writeln(msg_success);
		}
		else {
			writeln("[WARN ] " + msg_fail);
		}
	}
}

