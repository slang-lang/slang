#!/usr/local/bin/oscript

private object TestObject {
	private int mValue;

	public string =operator(string other) const {
		return string mValue;
	}

	public string ToString() const {
		return "TestObject";
	}
}

private object DerivedObject extends TestObject {
	private string mText;

	public string =operator(string other) const {
		return mText + " " + base.mValue;
	}

	public string ToString() const {
		return "DerivedObject";
	}
}

public void Main(int argc, string args) modify {
	TestObject obj = new TestObject();
	obj.mValue = 173;

	print("obj = " + obj);
	ObjectReceiver(Object obj);
	print("obj = " + obj);

	obj = ObjectProvider();
	print("obj = " + obj);
}

private DerivedObject ObjectProvider() modify {
	DerivedObject obj = new DerivedObject();
	obj.mText = "bla";

	return obj;
}

private bool ObjectReceiver(Object obj ref) modify {
	assert(obj);

	print("obj = " + obj);
	obj.mValue = obj.mValue++;
	print("obj = " + obj);

	return obj;
}

