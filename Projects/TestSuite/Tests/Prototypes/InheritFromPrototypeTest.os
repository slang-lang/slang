#!/usr/local/bin/oscript

public object BasePrototype<T> {
	public T mValue;
	
	public void Constructor(T value) {
		mValue = value;
	}

	public string =operator(string none) const {
		return "mValue = " + string mValue;
	}
}

// BEWARE: inheriting from prototypes is not supported because our AST::TreeGenerator cannot resolve its constraints
public object DerivedFromPrototype extends BasePrototype<int> {
	public void Constructor(int value) {
		assert(!"not supported");

		base.Constructor(value);
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1: inherit from prototype");

	DerivedFromPrototype derived = new DerivedFromPrototype(173);
	print(string derived);

	assert( "mValue = 173" == string derived );

	assert( derived is DerivedFromPrototype );
	assert( derived is Object );
	assert( derived is BasePrototype<int> );	// is operator does not support prototypes ;-(

	return true;
}
