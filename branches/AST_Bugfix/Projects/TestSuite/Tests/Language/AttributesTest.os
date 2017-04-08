#!/usr/local/bin/oscript

public stable namespace AttributeTest {
	public void Function1() {
		print("Function1");

		SubFunction1();
	}

	public void SubFunction1() {
		print("SubFunction1");

		SubFunction2();
	}

	public void SubFunction2() {
		print("SubFunction2");
	}

	public unstable object TestObject {
		public void Constructor() {
			print("Constructor()");
		}

		public void Destructor() {
			print("Destructor()");
		}

		public deprecated void deprecatedMethod() {
			print("deprecated method called");
		}

		public /*notimplemented*/ void notimplementedMethod() {
			print("not implemented method called");
		}

		public stable void stableMethod() {
			print("stable method called");
		}

		public unstable void unstableMethod() {
			print("unstable method called");
		}
	}

	public object ConstObject {
		private int mNumber;

		public void Constructor() {
			mNumber = 1;
		}

		public int GetNumber() const {
			return mNumber;
		}

		public void SetNumber(int value) modify {
			mNumber = value;
		}
	}
}

public void Main(int argc = 0, string argv = "") {
	AttributeTest.Function1();

	bla(1);

	AttributeTest.TestObject mTest = new AttributeTest.TestObject();

	mTest.deprecatedMethod();
	//mTest.notimplementedMethod();
	mTest.stableMethod();
	mTest.unstableMethod();

	AttributeTest.ConstObject value = new AttributeTest.ConstObject();
	print("value.GetNumber() = " + value.GetNumber());
	value.SetNumber(2);
	print("value.GetNumber() = " + value.GetNumber());

	print(getTwo());
}

private int getTwo() const {
	return 2;
}

private void bla() { }
private void bla(int num) { }

