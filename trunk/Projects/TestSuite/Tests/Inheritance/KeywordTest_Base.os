#!/usr/local/bin/oscript

public namespace Inheritance
{
	private object BaseObject
	{
		public number getValue() const
		{
			return 1;
		}
	}

	private object ExtendedObject
	{
		public number getValue() const
		{
			number baseValue = base.getValue();

			return 1 + baseValue;
		}
	}

	public object Main
	{
		public void Main(number argc, string argv)
		{
			assert( TestCase1() );
		}

		private bool TestCase1() const
		{
			BaseObject b = new BaseObject();
			ExtendedObject e = new ExtendedObject();

			print("b.getValue() = " + b.getValue());
			assert( b.getValue() == 1 );

			print("e.getValue() = " + e.getValue() );
			assert( e.getValue() == 2 );

			return true;
		}
	}
}
