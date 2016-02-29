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

	private object ExtendedObject extends BaseObject
	{
		public number getValue() const
		{
			number baseValue = 1 + base.getValue();

			return baseValue;
		}

		public number getBaseValue() const
		{
			return base.getValue();
		}
	}

	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
		}

		private bool TestCase1() const
		{
			this;
			base;

			BaseObject b = new BaseObject();
			ExtendedObject e = new ExtendedObject();

			print("b.getValue() = " + b.getValue());
			assert( b.getValue() == 1 );

			print("e.getBaseValue() = " + e.getBaseValue() );
			assert( e.getBaseValue() == 1 );

			print("e.getValue() = " + e.getValue() );
			assert( e.getValue() == 2 );

			return true;
		}
	}
}
