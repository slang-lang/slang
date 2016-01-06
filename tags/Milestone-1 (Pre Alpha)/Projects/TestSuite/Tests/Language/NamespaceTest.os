#!/usr/local/bin/oscript

public namespace Tests
{
	public namespace NamespaceTests
	{
		public object Test1
		{
			private string mName;

			public void Test1(string name const = "Test1")
			{
				mName = name;
			}

			public string getName() const
			{
				return mName;
			}
		}
	}
	
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			NamespaceTests.Test1 test1 = new Test1();
			print(test1.getName());
		}
	}
}
