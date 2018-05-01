#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	assert( OptionalParameterName(0, false, "foo") );

	OIsForObject o = new OIsForObject();
	assert( o.init(0, false) );
}

private bool OptionalParameterName(int, bool value, string) {
	return true;
}

private stable interface IIsForInterface {
	public void init(int, bool);
}

private object OIsForObject implements IIsForInterface {
	public void Constructor() {
	}

	public bool init(int /*param1*/, bool /*param2*/) {
		return true;
	}
}

