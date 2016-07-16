#!/usr/local/bin/oscript

public namespace Inheritance {

	private object BaseObject {
		private int mValue;

		public void BaseObject(int value) {
			print("BaseObject(" + value + ")");
			mValue = value;
		}

		public void ~BaseObject() {
			print("~BaseObject()");
		}

		public int getValue() const {
			return mValue;
		}

		public void setValue(int value) modify {
			mValue = value;
		}

		public void ThisMethodOnlyExistsInBaseObject() {
			print("ThisMethodOnlyExistsInBaseObject");
		}
	}

	private object DerivedObject extends BaseObject {
		public void DerivedObject(int value) {
			print("DerivedObject(" + value + ")");

			base.BaseObject(value);
		}

		public void ~DerivedObject() {
			print("~DerivedObject()");
		}

		public int getBaseValue() const {
			return base.getValue();
		}

		public int getValue() const {
			return 1 + base.getValue();
		}

		public void ThisMethodOnlyExistsInDerivedObject() {
			print("ThisMethodOnlyExistsInDerivedObject");
		}
	}

	private object ExtendedObject extends DerivedObject {
		public void ExtendedObject(int value) {
			print("ExtendedObject(" + value + ")");

			base.DerivedObject(value);
		}

		public void ~ExtendedObject() {
			print("~ExtendedObject()");
		}

		public int getValue() const {
			return 1 + base.getValue();
		}

		public int getBaseValue() const {
			return base.getValue();
		}

		public void ThisMethodOnlyExistsInExtendedObject() {
			print("ThisMethodOnlyExistsInExtendedObject");
		}
	}
}

public object Main {
	public void Main(int argc = 0, string argv = "") {
		assert( TestCase1() );
	}

	private bool TestCase1() const {
		Inheritance.BaseObject b = new Inheritance.BaseObject(1);
		Inheritance.DerivedObject d = new Inheritance.DerivedObject(1);
		Inheritance.ExtendedObject e = new Inheritance.ExtendedObject(1);

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

