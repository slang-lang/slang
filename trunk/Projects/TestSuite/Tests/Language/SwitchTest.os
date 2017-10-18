#!/usr/local/bin/oscript

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
	assert( TestCase6() );
	//assert( TestCase7() );	// this should fail
	assert( TestCase8() );
	assert( TestCase9() );
	assert( TestCase10() );
	assert( TestCase11() );
	assert( TestCase12() );
}

private bool TestCase1() const {
	print("TestCase 1: simple switch");

	int one = 1;
	switch ( one ) {
		case 1: {
			return true;
		}
		default: {
			return false;
		}
	}

	return false;
}

private bool TestCase2() const {
	print("TestCase 2: switch-expression parsing");

	int one = 1;
	switch ( one + 2 ) {
		case 1: { return false; }
		case 2: { return false; }
		case 3: { return true; }
		default: { return false; }
	}

	return false;
}

private bool TestCase3() const {
	print("TestCase 3: implicit continue");

	int one = 1;
	switch ( one ) {
		case 1: { print("case 1"); print("some other commands"); print("bla"); }
		case 2: { print("case 2"); break; }
		case 3: { assert( false ); break; }
		default: { print("default"); break; }
	}

	return true;
}

private bool TestCase4() const {
	print("TestCase 4: default");

	int one  = 1;
	switch ( one ) {
		case 0: { return false; }
		default: { return true; }
	}

	return false;
}

private bool TestCase5() const {
	print("TestCase 5: no default");

	switch ( 0 ) {
		case 1: { return false; }
		case 2: { return false; }
	}

	return true;
} 

private bool TestCase6() const {
	print("TestCase 6: case-expression parsing with continue");

	int one = 1;
	switch ( 2 ) {
		case (one + 1): { print("case (one + 1)"); one++; continue; }
		case 2: { print("case 2"); return true; }
	}

	return false;
}

private bool TestCase7() const {
	print("TestCase 7: double-default");

	switch ( 1 ) {
		default: { return true; }
		//default: { return false; }
	}

	return false;
}

private bool TestCase8() const {
	print("TestCase 8: default");

	int value;
	switch ( value ) {
		default: { return true; }
		case 1: { return false; }
		case 2: { return false; }
	}

	return false;
}

private bool TestCase9() const {
	print("TestCase 9: case without control-statement");

	switch ( 0 ) {
		case 0: { print("case 0"); break; }
		default: { print("default"); return false; }
	}

	return true;
}

private bool TestCase10() const {
	print("TestCase 10: case with continue");

	switch ( 2 ) {
		case 0: { print("case 0"); continue; }
		case 1: { assert( false ); }
		default: { print("default"); return true; }
	}

	return true;
}

private bool TestCase11() const {
	print("TestCase 11: inner-switch");

	int one;
	switch ( one ) {
		case 1: { assert( false ); }
		case 0: {
			print("case 0");

			int one = 1;
			switch ( one ) {
				case 0: { assert( false ); }
				case 1: { print("inner case 1"); return true; }
			}
		}
		default: { assert( false ); }
	}

	return false;
}

private bool TestCase12() const {
	print("TestCase 12: switch-loop");

	int value;
	switch ( value ) {
		case 5: { return true; }
		default: {
			print("default: " + value);
			value++;
			continue;
		}
	}

	return false;
}

