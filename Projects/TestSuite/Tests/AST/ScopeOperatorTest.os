#!/usr/local/bin/slang

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}


private object ScopeOperatorObject {
	public int mValue;

	public void Constructor(int value) {
		mValue = value;
	}

	public string toString() const {
		return string mValue;
	}
}

private bool TestCase1() {
	print("TestCase 1: scope operator with members");

	var scopeObj = new ScopeOperatorObject(173);
	var obj = Object scopeObj;

	print((ScopeOperatorObject obj).mValue);
	assert( (ScopeOperatorObject obj).mValue == 173 );

	return true;
}

private bool TestCase2() {
	print("TestCase 2: scope operator with methods");

	var scopeObj = new ScopeOperatorObject(1389);
	var obj = Object scopeObj;

	print((ScopeOperatorObject obj).toString());
	assert( (ScopeOperatorObject obj).toString() == "1389" );

	return true;
}

