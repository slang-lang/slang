#!/usr/local/bin/slang

public object BaseObject {
}

public object DerivedObject extends BaseObject {
}

public void Main( int argc, string args ) {
	var obj = new DerivedObject();
}

