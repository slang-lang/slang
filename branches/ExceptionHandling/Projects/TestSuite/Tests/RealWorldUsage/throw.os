#!/usr/local/bin/oscript

import System.Integer;

private void MethodThatThrows() throws {
	throw new int(42);
	throw new Integer(42);
}

public void Main(int argc = 0, string args = "") throws {
	MethodThatThrows();
}

