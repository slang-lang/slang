#!/usr/local/bin/oscript

private void BreakOnException() const {
	print("Break on exception...");

	try {
		throw 1;
	}
	catch (int e) {
		print("catch: " + e);
	}
	finally {
		print("finally");
	}
}

/*
// object orientated entry point
public object Main {
	public void Main(int argc, string args) {
		BreakOnException();
	}
}
*/

// structured execution entry point
public int Main(int argc, string args) {
	BreakOnException();

	return 0;
}

