#!/usr/local/bin/oscript

public namespace Tests
{
	public namespace NamespaceTests
	{
		public object Test1
		{
			private String mName;

			public void Test1(String name const = "Test1")
			{
				mName = name;
			}

			public String getName() const
			{
				return mName;
			}
		}
	}
	
	public object Main
	{
		public void Main(Number argc = 0, String argv = "")
		{
			NamespaceTests.Test1 test1 = new Test1();
			print(test1.getName());
		}
	}
}
