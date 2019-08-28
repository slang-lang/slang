#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	assert( EmptyMethodCall() );
}

private void EmptyMethod() {
}

private bool EmptyMethodCall() {
	EmptyMethod();

	return true;
}

