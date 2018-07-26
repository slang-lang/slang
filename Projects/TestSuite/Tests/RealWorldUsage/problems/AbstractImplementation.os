#!/usr/local/bin/oscript

public abstract object AbstractBase {
	protected int mSize = 1389;

	public int size() const {
		return mSize;
	}	
}

public object AbstractImplementation extends AbstractBase {
	public void Constructor() {
		base.Constructor();
	}

/*
	public string =operator(string none) const {
		return "mSize = " + mSize;
	}
*/
}

public void Main(int argc, string args) {
	var impl = AbstractBase new AbstractImplementation();

	print(string impl.size());
	print(string impl);
}

