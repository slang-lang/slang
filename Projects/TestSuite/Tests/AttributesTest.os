
namespace Main
{
	public object TestObject
	{
		public deprecated void deprecatedMethod() { }
		public notimplemented void notimplementedMethod() { }
		public stable void stableMethod() { }
		public unstable void unstableMethod() { }
	}

	public object Main
	{
		TestObject test;

		public void Main()
		{
			test.deprecatedMethod();
			test.notimplementedMethod();
			test.stableMethod();
			test.unstableMethod();
		}
	}
}
