#!/usr/local/bin/oscript

public object PrivateConstructor {
	private void Constructor() {
	}
}

public void Main(int argc, string args) {
	PrivateConstructor pc = new PrivateConstructor();
	assert(!"this should not be possible");
}

