#!/usr/local/bin/slang


public object BaseObject {
	public int Value = 1;
}

public object DerivedObject {
	public int DerivedValue = 2;
}


public void Main( int argc, string args ) {
	var obj = new DerivedObject();
}

