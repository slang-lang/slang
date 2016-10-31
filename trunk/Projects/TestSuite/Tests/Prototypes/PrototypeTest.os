#!/usr/local/bin/oscript

import System.Integer;
import System.String;

public prototype TestPrototype<T> {
	private T mValue;

	public void Constructor() {
		mValue = 0;
	}

	public void Constructor(T value) {
		mValue = value;
	}

	public T getValue() const {
		return mValue;
	}

	public void setValue(UNKOWN value) {
		mValue = value;
	}
}

public prototype AnotherPrototype<K: Object, V: Object> {
	private K mKey;
	private V mValue;

	public void Constructor(K key, V value) {
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

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
}

public bool TestCase1() {
	TestPrototype<int> proto = new TestPrototype<int>(173);
	print("proto.getValue() = " & proto.getValue());
	proto.setValue(1389);
	print("proto.getValue() = " & proto.getValue());

	AnotherPrototype<int, string> another = new AnotherPrototype<Integer, String>(new Integer(173), new String("1389"));
	print(string another.getKey());
	print(string another.getValue());
}

