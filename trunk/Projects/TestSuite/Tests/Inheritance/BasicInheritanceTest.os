#!/usr/local/bin/oscript

public namespace Inheritance
{
	public object BaseObject
	{
		public void ~BaseObject()
		{
		}

		public string getName() const
		{
			return "BaseObject";
		}
	}

	public object ExtendedObject extends BaseObject
	{
		public void ~ExtendedObject()
		{
		}

		public string getExtendedName() const
		{
			return "ExtendedObject";
		}

		public string getName() const
		{
			return "ExtendedObject::" + base.getName();
		}
	}

	public object Main
	{
		public void Main(int argc = 0, string argv = "")
		{
			assert( TestCase1() );
		}

		private bool TestCase1()
		{
			print("TestCase 1: ");

			BaseObject b = new BaseObject();
			ExtendedObject e = new ExtendedObject();

			print("b.getName() = " + b.getName());
			print("e.getName() = " + e.getName());
			print("e.getExtendedName() = " + e.getExtendedName());

			delete e;
			delete b;

			return true;
		}
	}
}
