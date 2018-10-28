#!/usr/local/bin/oscript

private object TestObject {
	private int value = false;
}

public void Main(int argc, string args) {
	InvalidParameter(0);
}

private void InvalidParameter(int value = true) {
}

