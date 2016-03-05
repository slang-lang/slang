#!/usr/local/bin/oscript

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

public prototype AnotherPrototype<object K, object V>
{
	private K mKey;
	private V mValue;

	public void AnotherPrototype(K key, V value)
	{
		mKey = key;
		mValue = value;
	}

	public K getKey() const {
		return mKey;
	}

	public V getValue() const {
		return mValue;
	}
}

public object Main
{
	public void Main(number argc = 0, string argv = "")
	{
		test();
	}

	public void test() {
		//TestPrototype<number> proto(100);
		//TestPrototype < number > proto(100);
		TestPrototype of number prototype = new TestPrototype of number(100);

/*
		print("Prototype value = " & prototype.getValue());

		prototype.setValue(17);

		print("Prototype value = " & prototype.getValue());
*/

		AnotherPrototype<number, string> another = new AnotherPrototype<number, string>(1, "1");
		another.getKey();
		another.getValue();
	}
}

