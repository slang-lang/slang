#!/usr/local/bin/oscript

public namespace MathOverloads {
	public object OverloadedObject {
		private int mNumber;

		public void Constructor(int one const) {
			mNumber = one;
		}

		public int GetNumber() const {
			return mNumber;
		}

		/////////////////////////////////////////////////////////////////////

		public OverloadedObject operator/(int other const) modify {
			print("operator/");
			mNumber = mNumber / other;

			return this;
		}

		public bool operator==(int other const) const {
			print("operator==(int)");
			return mNumber == other;
		}

		public OverloadedObject operator*(int other const) modify {
			print("operator*");
			mNumber = mNumber * other;

			return this;
		}

		public OverloadedObject operator%(int other const) modify {
			print("operator%");
			mNumber = mNumber % other;

			return this;
		}

		public OverloadedObject operator+(int other const) modify {
			print("operator+");
			mNumber = mNumber + other;

			return this;
		}

		public OverloadedObject operator-(int other const) modify {
			print("operator-");
			mNumber = mNumber - other;

			return this;
		}

		public OverloadedObject operator++() modify {
			print("operator++");
			mNumber = mNumber++;

			return this;
		}

		public OverloadedObject operator--() modify {
			print("operator--");
			mNumber = mNumber--;

			return this;
		}
	}
}

public void Main(int argc const = 0, string argv const = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );	//modulo operator only implemented for integer type
	assert( TestCase6() );
	assert( TestCase7() );
}

private bool TestCase1() const {
	print("TestCase1: using the overloaded plus operator");

	MathOverloads.OverloadedObject obj1 = new MathOverloads.OverloadedObject(1);

	obj1 = obj1 + 2;
	//assert(obj1 == 3);
	print("obj1.GetNumber() = " + obj1.GetNumber());

	if ( obj1 == 3 ) {
		return true;
	}

	return false;
}

private bool TestCase2() const {
	print("TestCase2: using the overloaded subtract operator");

	MathOverloads.OverloadedObject obj1 = new MathOverloads.OverloadedObject(1);

	obj1 = obj1 - 2;
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

	obj1 = obj1 * 2;
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

	obj1 = obj1 / 2;
	//assert( obj1 == 0.5 );
	print("obj1.GetNumber() = " + obj1.GetNumber());

	if ( obj1 == 2 ) {
		return true;
	}

	return false;
}

private bool TestCase5() const {
	print("TestCase5: using the overloaded modulo operator");

	MathOverloads.OverloadedObject obj1 = new MathOverloads.OverloadedObject(5);

	obj1 = obj1 % 2;
	//assert( obj1 == 0.5 );
	print("obj1.GetNumber() = " + obj1.GetNumber());

	if ( obj1 == 1 ) {
		return true;
	}

	return false;
}

private bool TestCase6() const {
	print("TestCase6: using the overloaded decrement operator");

	MathOverloads.OverloadedObject obj1 = new MathOverloads.OverloadedObject(5);

	obj1--;
	//assert( obj1 == 4 );
	print("obj1.GetNumber() = " + obj1.GetNumber());

	if ( obj1 == 4 ) {
		return true;
	}

	return false;
}

private bool TestCase7() const {
	print("TestCase7: using the overloaded increment operator");

	MathOverloads.OverloadedObject obj1 = new MathOverloads.OverloadedObject(5);

	obj1++;
	//assert( obj1 == 6 );
	print("obj1.GetNumber() = " + obj1.GetNumber());

	if ( obj1 == 6 ) {
		return true;
	}

	return false;
}
