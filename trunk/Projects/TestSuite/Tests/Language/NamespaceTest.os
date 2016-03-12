#!/usr/local/bin/oscript

public namespace Tests sealed
{
	public namespace NamespaceTests sealed
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
		public void Main(int argc = 0, string argv = "")
		{
			NamespaceTests.Test1 test1 = new NamespaceTests.Test1();
			print(test1.getName());
		}
	}
}
