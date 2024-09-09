#!/usr/local/bin/slang

public void Main( int argc = 0, string args = "" ) {
	// assign
	assert( TestAssignEnumToInt() );
	//assert( TestAssignIntToEnum() );	// this test should fail

	// equals
	assert( TestEnumEqualInt() );
	assert( TestIntEqualEnum() );

	// less

	// less then

	// greater

	// greater then

	// unequals
	assert( TestEnumUnequalInt() );
	assert( TestIntUnequalEnum() );
}

enum TestEnum {
	Off = 0,
	On = 1;
}


bool TestAssignEnumToInt() {
	print( "TestCase: assign enum to int" );

	int i = 0;

	i = TestEnum.On;

	return i == 1;
}

/*
bool TestAssignIntToEnum() {
	print( "TestCase: assign int to enum" );

	TestEnum e = TestEnum.Off;

	e = 1;

	return e == TestEnum.On;
}
*/

bool TestEnumEqualInt() {
	print( "TestCase: enum equals int" );

	return 1 == TestEnum.On;
}

bool TestIntEqualEnum() {
	print( "TestCase: int equals enum" );

	return TestEnum.On == 1;
}

bool TestEnumUnequalInt() {
	print( "TestCase: enum unequal int" );

	return TestEnum.On != 42;
}

bool TestIntUnequalEnum() {
	print( "TestCase: int unequal enum" );

	return 17 != TestEnum.Off;
}

