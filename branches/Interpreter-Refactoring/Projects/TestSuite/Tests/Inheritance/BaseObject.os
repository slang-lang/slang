
public object BaseObject {
	private int mValue;

	public void BaseObject() {
		print("BaseObject::BaseObject()");
	}

	public void ~BaseObject() {
		print("BaseObject::~BaseObject()");
	}

	public int getValue() const {
		return mValue;
	}

	public void setValue(int value) modify {
		mValue = value;
	}
	
	public string ToString() const {
		return "BaseObject { mValue = " + mValue + " }";
	}
}

