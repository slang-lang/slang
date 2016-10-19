#!/usr/local/bin/oscript

public namespace MathOverloads {
	private object OverloadedObject {
		private int mNumber;

		public void OverloadedObject(int one const) {
			mNumber = one;
		}

		public int GetNumber() const {
			return mNumber;
		}

		/////////////////////////////////////////////////////////////////////

		public bool operator==(int other const) const {
			print("operator==(int)");
			return mNumber == other;
		}

		public bool operator==(MathOverloads.OverloadedObject other const ref) const {
			print("operator==(OverloadedObject)");
			return mNumber == other.GetNumber();
		}

		public void operator*(MathOverloads.OverloadedObject other const ref) modify {
			print("operator*(OverloadedObject)");
			mNumber = mNumber * other.GetNumber();
		}

		public void operator%(MathOverloads.OverloadedObject other const ref) modify {
			print("operator%(OverloadedObject)");
			mNumber = mNumber % other.GetNumber();
		}

		public void operator+(MathOverloads.OverloadedObject other const ref) modify {
			print("operator+(OverloadedObject)");
			mNumber = mNumber + other.GetNumber();
		}

		public void operator-(MathOverloads.OverloadedObject other const ref) modify {
			print("operator-(OverloadedObject)");
			mNumber = mNumber - other.GetNumber();
		}

		public void operator/(MathOverloads.OverloadedObject other const ref) modify {
			print("operator/(OverloadedObject)");
			mNumber = mNumber / other.GetNumber();
		}
	}
}

public void Main(int argc const = 0, string argv const = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
}

private bool TestCase1() const {
	print("TestCase1: using the overloaded plus operator");

	MathOverloads.OverloadedObject obj1 = new MathOverloads.OverloadedObject(1);
	MathOverloads.OverloadedObject obj2 = new MathOverloads.OverloadedObject(2);

	obj1 = obj1 + obj2;
	assert(obj1 == 3);
	print("obj1.GetNumber() = " + obj1.GetNumber());
	
	if ( obj1 == 3 ) {
		return true;
	}

	return false;
}

private bool TestCase2() const {
	print("TestCase2: using the overloaded subtract operator");

	MathOverloads.OverloadedObject obj1 = new MathOverloads.OverloadedObject(1);
	MathOverloads.OverloadedObject obj2 = new MathOverloads.OverloadedObject(2);

	obj1 = obj1 - obj2;
	//assert( obj1 == -1 );
	print("obj1.GetNumber() = " + obj1.GetNumber());

	if ( obj1 == obj1.GetNumber() ) {
		return true;
	}

	return false;
}

private bool TestCase3() const {
	print("TestCase3: using the overloaded multiply operator");

	MathOverloads.OverloadedObject obj1 = new MathOverloads.OverloadedObject(1);
	MathOverloads.OverloadedObject obj2 = new MathOverloads.OverloadedObject(2);

	obj1 = obj1 * obj2;
	//assert( obj1 == 2 );
	print("obj1.GetNumber() = " + obj1.GetNumber());

	if ( obj1 == 2 ) {
		return true;
	}

	return false;
}

private bool TestCase4() const {
	print("TestCase4: using the overloaded divide operator");

	MathOverloads.OverloadedObject obj1 = new MathOverloads.OverloadedObject(4);
	MathOverloads.OverloadedObject obj2 = new MathOverloads.OverloadedObject(2);

	obj1 = obj1 / obj2;
	//assert( obj1 == 2 );
	print("obj1.GetNumber() = " + obj1.GetNumber());

	if ( obj1 == 2 ) {
		return true;
	}

	return false;
}

private bool TestCase5() const {
	print("TestCase5: using the overloaded modulo operator");

	MathOverloads.OverloadedObject obj1 = new MathOverloads.OverloadedObject(5);
	MathOverloads.OverloadedObject obj2 = new MathOverloads.OverloadedObject(2);

	obj1 = obj1 % obj2;
	//assert( obj1 == 0.5 );
	print("obj1.GetNumber() = " + obj1.GetNumber());

	if ( obj1 == 1 ) {
		return true;
	}

	return false;
}

