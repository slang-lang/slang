#!/usr/local/bin/oscript

import System.Object;

public object IObjectImplementation implements /*System.*/IObject {
	public void Constructor() {
	}
	
	public string GetObjectType() const {
		return "IObjectImplementation";
	}

	public string ToJsonString() const {
		return "{ }";
	}
	
	public string ToString() const {
		return "IObjectImplementation.ToString()";
	}
}

public object TObjectDerivate extends /*System.*/TObject {
	public string GetObjectType() const {
		return "TObjectDerivate";
	}

	public string ToString() const {
		return "TObjectDerivate.ToString()";
	}
}

public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( ! TestCase3() );
}

private bool TestCase1() const {
	print("TestCase 1");

	IObjectImplementation obj = new IObjectImplementation();

	print(obj.ToString());

	return obj;
}

private bool TestCase2() const {
	print("TestCase 2");

	TObjectDerivate obj = new TObjectDerivate();

	print(obj.ToString());

	return obj;
}

private bool TestCase3() const {
	print("TestCase 3");

	TObjectDerivate obj;
	print(obj);

	return obj;
}

