#!/usr/local/bin/oscript

public namespace Inheritance
{
	private object BaseObject
	{
		private number mValue;

		public void BaseObject(number value)
		{
			print("BaseObject::BaseObject(" + value + ")");
			mValue = value;
		}

		public void ~BaseObject()
		{
			print("BaseObject::~BaseObject()");
		}

		public number getValue() const
		{
			return mValue;
		}

		public void setValue(number value) modify
		{
			mValue = value;
		}

		public void ThisMethodOnlyExistsInBaseObject()
		{
			print("ThisMethodOnlyExistsInBaseObject");
		}
	}

	private object DerivedObject extends BaseObject
	{
		protected BaseObject mBaseObject;

		public void DerivedObject(number value)
		{
			print("DerivedObject::DerivedObject(" + value + ")");

			base.BaseObject(value);

			//mBaseObject = new BaseObject(5);
			mBaseObject.setValue(9);
		}

		public void ~DerivedObject()
		{
			print("DerivedObject::~DerivedObject()");
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

		public void ThisMethodOnlyExistsInDerivedObject()
		{
			print("ThisMethodOnlyExistsInDerivedObject");
		}
	}

	private object ExtendedObject extends DerivedObject
	{
		public void ExtendedObject(number value)
		{
			print("ExtendedObject::ExtendedObject(" + value + ")");

			base.DerivedObject(1);
		}

		public void ~ExtendedObject()
		{
			print("ExtendedObject::~ExtendedObject()");
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

		public void ThisMethodOnlyExistsInExtendedObject()
		{
			print("ThisMethodOnlyExistsInExtendedObject");
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

			e.ThisMethodOnlyExistsInBaseObject();
			e.ThisMethodOnlyExistsInDerivedObject();
			e.ThisMethodOnlyExistsInExtendedObject();

delete e;
delete d;
delete b;

			return true;
		}
	}
}
