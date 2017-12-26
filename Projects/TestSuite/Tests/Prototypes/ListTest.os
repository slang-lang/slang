#!/usr/local/bin/oscript

private object List<T> {
	private int mSize;
	private T mLast;

	public void Constructor() {
		mSize = 0;
	}

	public bool empty() const {
		return mSize == 0;
	}

	public T peek() const throws {
		if ( empty() ) {
			throw new int(42);
		}

		return mLast;
	}

	public void pop_back() modify {
		mSize--;
	}

	public void push_back(T value) modify {
		mLast = value;
		mSize++;
	}

	public int size() const {
		return mSize;
	}
}

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
}

private bool TestCase1() {
	print("TestCase 1: List<int>");

	List<int> values = new List<int>();

	print("values.size() = " + values.size());

	values.push_back(5);
	print(values.peek());

	values.push_back(17);
	print(values.peek());

	print("values.size() = " + values.size());

	return true;
}

private bool TestCase2() {
	print("TestCase 2: List<string>");

	List<string> strings = new List<string>();

	strings.push_back("O664O");
	print(strings.peek());

	strings.push_back("O173O");
	print(strings.peek());

	strings.push_back("O1389O");
	print(strings.peek());

	return true;
}

private bool TestCase3() {
	print("TestCase 3: raw prototype");

	List list = new List();
	assert( list is Object );

	assert( typeid(list) == "List<Object>" );

	list.push_back(new Object());

	return true;
}

