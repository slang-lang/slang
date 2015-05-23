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

	public object stable Main
	{
		private TestObject mTest;

		public void Main()
		{
			mTest = new TestObject();

			mTest.deprecatedMethod();
			//mTest.notimplementedMethod();
			mTest.stableMethod();
			mTest.unstableMethod();
/*
			TestObject tmp = new TestObject();
			//tmp runs out of scope and should now be automatically deleted
*/
		}

		public void ~Main()
		{
			delete mTest;
		}
	}
}
