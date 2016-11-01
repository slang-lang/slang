#!/usr/local/bin/oscript

import System.Integer;
import System.String;

public prototype Prototype<T> {
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

	public void setValue(T value) {
		mValue = value;
	}
}

public prototype AnotherPrototype<K, V> {
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
	print("TestCase 1");

	print("Prototype<int>");
	Prototype<int> proto = new Prototype<int>(173);
	print("proto.getValue() = " + proto.getValue());
	proto.setValue(1389);
	print("proto.getValue() = " + proto.getValue());

	print("AnotherPrototype<int, string>");
	AnotherPrototype<int, string> another = new AnotherPrototype<int, string>(173, "1389");
	print("another.getKey() = " + another.getKey());
	print("another.getValue() = " + another.getValue());

	return true;
}

