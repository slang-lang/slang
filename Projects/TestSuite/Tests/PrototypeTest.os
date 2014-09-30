
public prototype TestPrototype
{
	private UNKNOWN mValue;

	public void TestPrototype() {
		mValue = 0;
	}

	public void TestPrototype(UNKNOWN value) {
		mValue = value;
	}

	public UNKNOWN getValue() const {
		return mValue;
	}

	public void setValue(UNKOWN value) {
		mValue = value;
	}
}


public object Main
{
	public void test() {
		//TestPrototype<Number> proto(100);
		//TestPrototype < Number > proto(100);
		TestPrototype of Number prototype = new TestPrototype of Number(100);
/*
		print("Prototype value = " & prototype.getValue());

		prototype.setValue(17);

		print("Prototype value = " & prototype.getValue());
*/
	}
}
