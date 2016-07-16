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
		public void TestObject() {
			print("TestObject()");
		}

		public void ~TestObject() {
			print("~TestObject()");
		}

		public deprecated void deprecatedMethod() {
			print("deprecated method called");
		}

		public notimplemented void notimplementedMethod() {
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

		public void ConstObject() {
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

public stable object Main {
//	private TestObject mTest;

	public void Main(int argc = 0, string argv = "") {
		AttributeTest.TestObject mTest;

		AttributeTest.Function1();

		bla(1);

		mTest = new AttributeTest.TestObject();

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
}

