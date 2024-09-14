#!/usr/local/bin/slang

public object Template<T> {
	public T mValue;

	public void Constructor(T value) {
		mValue = value;
	}

	public string =operator() {
		return string mValue;
	}
}

public object Derived extends Template<int> {
	public void Constructor(int value) {
		base.Constructor(value);
	}
}

public void Main(int argc, string args) {
	var obj1 = new Derived(1389);
	var obj2 = new Template<int>(173);

	print( cast<Template<int>>( obj1 ) );
	print( Template<int> obj1 );
}

