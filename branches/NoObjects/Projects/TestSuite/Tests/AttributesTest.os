
public namespace Main
{
	public object TestObject
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

	public object Main
	{
		private TestObject mTest;

		public void Main()
		{
			mTest = new TestObject();

			mTest.deprecatedMethod();
			//mTest.notimplementedMethod();
			mTest.stableMethod();
			mTest.unstableMethod();
		}

		public void ~Main()
		{
			delete mTest;
		}
	}
}
