#!/usr/local/bin/slang

private object TestObject {
	public int mValue;

	public string =operator(string other) const {
		return string mValue;
	}

	public string ToString() const {
		return "TestObject";
	}
}

private object DerivedObject extends TestObject {
	public string mText;

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

	print("obj = " + string obj);
	ObjectReceiver(Object obj);
	print("obj = " + string obj);

	obj = TestObject ObjectProvider();
	print("obj = " + string obj);
}

private DerivedObject ObjectProvider() modify {
	DerivedObject obj = new DerivedObject();
	obj.mText = "bla";

	return obj;
}

private bool ObjectReceiver(Object obj ref) modify {
	assert(obj);

	TestObject to = TestObject obj;

	print("obj = " + string to);
	to.mValue = to.mValue++;
	print("obj = " + string obj);

	return bool obj;
}

