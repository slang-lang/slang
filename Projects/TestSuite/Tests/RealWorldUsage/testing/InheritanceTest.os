#!/usr/local/bin/slang

public object Base {
}

public object Derived extends Base {
}

public object Another extends Derived {
}

public void Main(int argc, string args) {
	print("Main");

	var another = new Another();

	assert( another is Base );
}

