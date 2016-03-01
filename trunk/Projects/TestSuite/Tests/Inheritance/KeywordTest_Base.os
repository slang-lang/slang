#!/usr/local/bin/oscript

public namespace Inheritance
{
	private object BaseObject
	{
		private number mValue;

		public void BaseObject(number value)
		{
			mValue = value;
		}

		public number getValue() const
		{
			return mValue;
		}
	}

	private object DerivedObject extends BaseObject
	{
		public void DerivedObject(number value)
		{
			base.BaseObject(value);
		}

		public number getBaseValue() const
		{
			return base.getValue();
		}

		public number getValue() const
		{
			number baseValue = 1 + base.getValue();

			return baseValue;
		}
	}

	private object ExtendedObject extends DerivedObject
	{
		public void ExtendedObject(number value)
		{
			base.DerivedObject(1);
		}

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
			BaseObject b = new BaseObject(1);
			DerivedObject d = new DerivedObject(1);
			ExtendedObject e = new ExtendedObject(1);

			print("b.getValue() = " + b.getValue());
			assert( b.getValue() == 1 );

			print("d.getValue() = " + d.getValue());
			assert( d.getValue() == 2 );

			print("d.getBaseValue() = " + d.getBaseValue() );
			assert( d.getBaseValue() == 1 );

			print("e.getValue() = " + e.getValue() );
			assert( e.getValue() == 3 );

			print("e.getBaseValue() = " + e.getBaseValue() );
			assert( e.getBaseValue() == 2 );

			return true;
		}
	}
}
