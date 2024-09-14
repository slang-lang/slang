#!/usr/local/bin/slang

public object TestObject {
	public int Value = 1;
}

public void Main( int argc, string args ) {
	var obj = new TestObject();

	obj.Value += 1;
	print( obj.Value );

	obj.Value += obj.Value;
	print( obj.Value );
}

