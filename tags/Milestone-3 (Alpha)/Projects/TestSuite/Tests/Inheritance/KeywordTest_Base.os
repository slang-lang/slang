#!/usr/local/bin/oscript

public namespace Inheritance {

	private object BaseObject {
		private int mValue;

		public void Constructor(int value) {
			print("Constructor(" + value + ")");
			mValue = value;
		}

		public void Destructor() {
			print("Destructor()");
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

	private object DerivedObject extends Inheritance.BaseObject {
		public void Constructor(int value) {
			print("Constructor(" + value + ")");

			base.Constructor(value);
		}

		public void Destructor() {
			print("Destructor()");
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

	private object ExtendedObject extends Inheritance.DerivedObject {
		public void Constructor(int value) {
			print("Constructor(" + value + ")");

			base.Constructor(value);
		}

		public void Destructor() {
			print("Destructor()");
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

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
}

private bool TestCase1() const {
	print("TestCase 1");

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

