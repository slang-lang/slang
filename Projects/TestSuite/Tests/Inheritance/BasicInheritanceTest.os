#!/usr/local/bin/oscript

public namespace Inheritance
{
	public object BaseObject
	{
		public string getName() const
		{
			return "BaseObject";
		}
	}

	public object ExtendedObject extends BaseObject
	{
		public string getExtendedName() const
		{
			return "ExtendedObject";
		}

		public string getName() const
		{
			return "ExtendedObject";
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

			BaseObject b = new BaseObject();
			ExtendedObject e = new ExtendedObject();

			print("b.getName = " + b.getName());
			print("e.getName = " + e.getName());
			print("e.getExtendedName = " + e.getExtendedName());

			delete e;
			delete b;

			return true;
		}
	}
}
