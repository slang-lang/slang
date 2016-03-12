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
	public void Main(int argc = 0, string argv = "")
	{
		test();
	}

	public void test() {
		//TestPrototype<int> proto(100);
		//TestPrototype < int > proto(100);
		TestPrototype of int prototype = new TestPrototype of int(100);

/*
		print("Prototype value = " & prototype.getValue());

		prototype.setValue(17);

		print("Prototype value = " & prototype.getValue());
*/

		AnotherPrototype<int, string> another = new AnotherPrototype<int, string>(1, "1");
		another.getKey();
		another.getValue();
	}
}

