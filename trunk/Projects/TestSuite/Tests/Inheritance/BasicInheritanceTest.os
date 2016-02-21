#!/usr/local/bin/oscript

public namespace BasicInheritanceTest
{
	public interface IDummyInterface
	{
		public string getName() const;
	}

	public object Base
	{
		public string getBaseName() const
		{
			return "Base";
		}
	}

	public object Extended extends Base, implements IDummyInterface
	{
		public string getExtendedName() const
		{
			return "Extended";
		}

		public string getName() const
		{
			return "Extended";
		}
	}

	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
		}

		private bool TestCase1()
		{
			print("TestCase 1: ");

			Base base = new Base();
			Extended extended = new Extended();

			print("base.getBaseName = " + base.getBaseName());
			print("extended.getBaseName = " + extended.getBaseName());
			print("extended.getExtendedName = " + extended.getExtendedName());

			delete extended;
			delete base;

			return true;
		}
	}
}
