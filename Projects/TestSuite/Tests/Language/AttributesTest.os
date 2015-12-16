#!/usr/local/bin/oscript

public namespace stable AttributeTest
{
	public object unstable TestObject
	{
		public deprecated void deprecatedMethod()
		{
			print("deprecated method called");
		}

		public notimplemented void notimplementedMethod()
		{
			print("not implemented method called");
		}

		public stable void stableMethod()
		{
			print("stable method called");
		}

		public unstable void unstableMethod()
		{
			print("unstable method called");
		}
	}

	public object StaticObject
	{
		public number GetOne() static
		{
			return number(1);
		}
	}

	public object ConstObject
	{
		private number mNumber;

		public void ConstObject()
		{
			mNumber = 1;
		}

		public number GetNumber() const
		{
			return mNumber;
		}

		public void SetNumber(number value) modify
		{
			mNumber = value;
		}
	}

	public object stable Main
	{
		private TestObject mTest;

		public void Main(number argc = 0, string argv = "") modify
		{
			mTest = new TestObject();

			mTest.deprecatedMethod();
			//mTest.notimplementedMethod();
			mTest.stableMethod();
			mTest.unstableMethod();

			//number one = StaticObject.GetOne();

			ConstObject value = new ConstObject();
			print("value.GetNumber() = " + value.GetNumber());
			value.SetNumber(2);
			print("value.GetNumber() = " + value.GetNumber());

			print(getTwo());

			//delete value;
		}

		public void ~Main()
		{
			delete mTest;
		}
		
		private number getTwo() const
		{
			return 2;
		}
	}
}
