#!/usr/local/bin/oscript

public namespace NamespaceTests {
	public object Test1 {
		private string mName;

		public void Constructor(string name const = "Test1") {
			mName = name;
		}

		public string getName() const {
			return mName;
		}
	}
}

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
}

private bool TestCase1() const {
	NamespaceTests.Test1 test1 = new NamespaceTests.Test1();
	print(test1.getName());

	return true;
}

