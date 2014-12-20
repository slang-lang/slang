
namespace Main
{
	public object TestObject
	{
		public deprecated void deprecatedMethod()
		{
			print("you should see this");
		}
		public notimplemented void notimplementedMethod()
		{
			print("you should NOT see this");
		}
		public stable void stableMethod()
		{
			print("you should see this");
		}
		public unstable void unstableMethod()
		{
			print("you should see this");
		}
	}

	public object Main
	{
		private TestObject test;

		public void Main()
		{
			test.deprecatedMethod();
			//test.notimplementedMethod();
			test.stableMethod();
			test.unstableMethod();
		}
	}
}
