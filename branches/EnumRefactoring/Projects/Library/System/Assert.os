
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

/*
public void assert(bool condition, string message) {
	if ( !condition ) {
		writeln("failed with message \"" + message + "\"");

		assert(condition);
	}
}
*/

public void debug(bool condition, string msg_success, string msg_fail) {
	if ( condition ) {
		print(msg_success);
	}
	else {
		print("[DEBUG] " + msg_fail);
	}
}

public void error(bool condition, string msg_success, string msg_fail) {
	if ( condition ) {
		print(msg_success);
	}
	else {
		print("[ERROR] " + msg_fail);
	}
}

public void warn(bool condition, string msg_success, string msg_fail) {
	if ( condition ) {
		print(msg_success);
	}
	else {
		print("[WARN ] " + msg_fail);
	}
}

