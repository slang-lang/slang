#!/usr/local/bin/oscript

public namespace Tests
{
	public namespace Inheritance
	{
		public object Base
		{
			public string getBaseName() const
			{
				return "Base";
			}
		}

		public object Extended extends public Base
		{
			public string getExtendedName() const
			{
				return "Extended";
			}
		}

		public object Main
		{
			public void Main(number argc = 0, string argv = "")
			{
				test();
			}

			private void test()
			{
				Base base = new Base();
				Extended extended = new Extended();

				print("base.getBaseName = " & base.getBaseName());
				print("extended.getBaseName = " & extended.getBaseName());
				print("extended.getExtendedName = " & extended.getExtendedName());

				delete base;
				delete extended;
			}
		}
	}
}
