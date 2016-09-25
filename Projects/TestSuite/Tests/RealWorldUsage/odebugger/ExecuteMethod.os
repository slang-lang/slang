#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc, string args) {
		print("Main()");

		print("done.");
	}

	private void Method(int value) {
		print("Method(" + value + ")");
	}

	private string Method(string value) {
		print("Method('" + value + "')");
		return value;
	}
}

