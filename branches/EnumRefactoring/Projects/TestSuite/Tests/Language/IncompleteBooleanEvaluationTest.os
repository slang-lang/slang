#!/usr/local/bin/oscript

public void Main(int argc = 0, string args = "") {
	// if-tests
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	// switch-tests
	assert( TestCase5() );
	assert( TestCase6() );
	// while-tests
	assert( TestCase7() );
	assert( TestCase8() );
	// NAND tests
	assert( TestCase9() );
	// NOR tests
	assert( TestCase10() );
}

private bool TestCase1() {
	print("TestCase 1: if");

	if ( true || false ) {
		print("true || false => if-block");
	}
	else {
		assert( false );
	}

	return true;
}

private bool TestCase2() {
	print("TestCase 2: if");

	if ( true || WriteFalse() ) {
		print("true || false => if-block");
	}
	else {
		assert( false );
	}

	return true;
}

private bool TestCase3() {
	print("TestCase 3: if");

	if ( false && true ) {
		assert( false );
	}
	else {
		print("false && true => else-block");
	}

	return true;
}

private bool TestCase4() {
	print("TestCase 4: if");

	if ( false && WriteFalse() ) {
		assert( false );
	}
	else {
		print("false && false => else-block");
	}

	return true;
}

private bool TestCase5() {
	print("TestCase 5: switch");

	switch ( true || WriteFalse() ) {
		case true: { print("true || false"); break; }
		default: { assert( false ); return false; }
	}

	return true;
}

private bool TestCase6() {
	print("TestCase 6: switch");

	switch ( false && WriteFalse() ) {
		case false: { print("false && false"); break; }
		default: { assert( false ); return false; }
	}

	return true;
}

private bool TestCase7() {
	print("TestCase 7: while");

	while ( true || WriteFalse() ) {
		print("true || false");
		break;
	}

	return true;
}

private bool TestCase8() {
	print("TestCase 8: while");

	while ( false && WriteFalse() ) {
		assert( false );
	}

	return true;
}

private bool TestCase9() {
	print("TestCase 9: NAND");

	if ( false !& WriteFalse() ) {
		print("false !& false");
	}
	else {
		assert( false );
	}

	return true;
}

private bool TestCase10() {
	print("TestCase 10: NOR");

	if ( true !| WriteFalse() ) {
		assert( false );
	}
	else {
		print("true !| false");
	}

	return true;
}

private bool WriteFalse() {
	print("false");

	assert( false );
	return false;
}

private bool WriteTrue() {
	print("true");

	assert( false );
	return false;
}

