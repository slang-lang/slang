#!/usr/local/bin/oscript

public namespace InstanciationTest {
	public object OuterObject {

		public object InnerObject {
			public string mValue;

			public void InnerObject(string value) {
				print("InnerObject(\"" + value + "\")");

				mValue = value;
			}

			public void ~InnerObject() {
				print("~InnerObject()");
			}
		}


		private string mValue;

		public void OuterObject(string value) {
			print("OuterObject(\"" + value + "\")");

			mValue = value;
		}

		public void ~OuterObject() {
			print("~OuterObject()");
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

