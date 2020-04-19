#!/usr/local/bin/slang

public object BaseObject {
	public void Destructor() {
		print("BaseObject.Destructor()");
	}

	public string getName() const {
		return "BaseObject";
	}
}

public object ExtendedObject extends BaseObject {
	public void Destructor() {
		print("ExtendedObject.Destructor()");
	}

	public string getExtendedName() const {
		return "ExtendedObject";
	}

	public string getName() const {
		//return "ExtendedObject." + base.getName();
		return "ExtendedObject";
	}
}

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1: ");

	BaseObject b = new BaseObject();
	ExtendedObject e = new ExtendedObject();

	print("b.getName() = " + b.getName());
	print("e.getName() = " + e.getName());
	print("e.getExtendedName() = " + e.getExtendedName());

	delete e;
	delete b;

	return true;
}

