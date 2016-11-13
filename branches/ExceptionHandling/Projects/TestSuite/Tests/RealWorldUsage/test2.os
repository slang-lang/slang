#!/usr/local/bin/oscript

public object BaseObject {
	protected string mName;
	private string mType;
	protected float mValue;

	public void Constructor(string name) {
		mName = name;
		mType = "BaseObject";
		mValue = 1.f;
	}

	public string getName() const {
		return mName;
	}

	public string getType() const {
		return mType;
	}

	public float getValue() const {
		return mValue;
	}
}

public object DerivedObject extends BaseObject {
	private string mType;

	public void Constructor(string name, string type, float value) {
		mName = name;
		mType = "DerivedObject";
		mValue = value;
	}

	public string getType() const {
		return mType;
	}
}

private BaseObject baseobj;
private DerivedObject derived;

public void Main(int argc, string argv) {
	baseobj = new BaseObject("baseobj");
	print("name = " + baseobj.getName());
	print("type = " + baseobj.getType());
	print("value = " + baseobj.getValue());

	derived = new DerivedObject("derived", "DerivedObject", 2.f);
	print("name = " + derived.getName());
	print("type = " + derived.getType());
	print("value = " + derived.getValue());
}

public void test1() const {
	print("name = " + baseobj.mValue);
	print("type = " + baseobj.mValue);
	print("value = " + baseobj.mValue);
}

