#!/usr/local/bin/oscript

public namespace InstanciationTest {
	public object OuterObject {

		public object InnerObject {
			public string mValue;

			public void Constructor(string value) {
				print("Constructor(\"" + value + "\")");

				mValue = value;
			}

			public void Destructor() {
				print("Destructor()");
			}
		}


		public string mValue;

		public void Constructor(string value) {
			print("Constructor(\"" + value + "\")");

			mValue = value;
		}

		public void Destructor() {
			print("Destructor()");
		}
	}
}

public void Main(int arc = 0, string argv = "") {
	assert( TestCase1() );
}

private bool TestCase1() const {
	InstanciationTest.OuterObject outer = new InstanciationTest.OuterObject("outer");
	print("outer.mValue = " + outer.mValue);

	InstanciationTest.OuterObject.InnerObject inner = new InstanciationTest.OuterObject.InnerObject("inner");
	print("inner.mValue = " + inner.mValue);

	return true;
}

