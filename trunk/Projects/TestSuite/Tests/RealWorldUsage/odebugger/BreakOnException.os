#!/usr/local/bin/oscript

private void BreakOnException() const {
	print("Break on exception...");

	try {
		throw 1;
	}
	catch {
		print("catch");
	}
	finally {
		print("finally");
	}
}

/*
public object Main {
	public void Main(int argc, string args) {
		BreakOnException();
	}
}
*/

public int Main(int argc, string args) {
	BreakOnException();

	return 0;
}

