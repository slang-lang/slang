
public prototype TestPrototype
{
	private UNKNOWN mValue;

	public TestPrototype(UNKNOWN value) {
		mValue = value;
	}

	public UNKNOWN getValue() const {
		return mValue;
	}

	public Void setValue(UNKOWN value) {
		mValue = value;
	}
}


public object Main
{
	public Void Main() { }
	
	public Void test() {
		TestPrototype<Number> proto(100);

		print("Prototype value = " & proto.getValue());

		proto.setValue(17);

		print("Prototype value = " & proto.getValue());
	}
}
