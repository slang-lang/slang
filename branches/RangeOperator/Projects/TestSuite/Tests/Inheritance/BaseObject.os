
public object BaseObject {
	private int mValue;

	public void Constructor() {
		print("BaseObject.Constructor()");
	}

	public void Destructor() {
		print("BaseObject.Destructor()");
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

