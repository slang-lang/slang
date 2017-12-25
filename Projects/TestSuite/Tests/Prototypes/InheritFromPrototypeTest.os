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
	}
}

public void Main(int argc = 0, string args = "") {
	assert( false );
}

