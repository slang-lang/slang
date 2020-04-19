#!/usr/local/bin/oscript

public object Base extends Derived {
}

public object Derived extends Base {
}

public void Main(int argc, string args) {
	print("Main");

	var b = new Base();
}

