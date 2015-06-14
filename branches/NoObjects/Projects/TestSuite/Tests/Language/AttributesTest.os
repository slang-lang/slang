#!/usr/bin/oscript

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
		public Number GetOne() static
		{
			return Number(1);
		}
	}

	public object ConstObject
	{
		Number mNumber;

		public void ConstObject()
		{
			mNumber = 1;
		}

		public Number GetNumber() const
		{
			return mNumber;
		}

		public void SetNumber(Number value) modify
		{
			mNumber = value;
		}
	}

	public object stable Main
	{
		private TestObject mTest;

		public void Main(Number argc = 0, String argv = "")
		{
			{
				mTest = new TestObject();

				mTest.deprecatedMethod();
				//mTest.notimplementedMethod();
				mTest.stableMethod();
				mTest.unstableMethod();
			}

			{
				//Number one = StaticObject.GetOne();
			}

			{
				ConstObject number = new ConstObject();
				print(number.GetNumber());
				number.SetNumber(2);
				print(number.GetNumber());

				delete number;
			}
		}

		public void ~Main()
		{
			delete mTest;
		}
	}
}
