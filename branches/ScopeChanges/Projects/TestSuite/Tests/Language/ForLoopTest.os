#!/usr/local/bin/oscript

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
	assert( TestCase6() );
	assert( TestCase7() );
	assert( TestCase8() );
	assert( TestCase9() );
	assert( TestCase10() );
}

private bool TestCase1() const {
	int count;

	for ( int loop1 = 0; loop1 < 5; loop1++ ) {
		print("loop1 = " + loop1);
		assert( loop1 < 5 );

		count++;
	}

	return count == 5;
}

private bool TestCase2() const {
	int count;

	for ( int loop2 = 0; loop2 < 10; loop2 += 1 ) {
		count++;

		print("loop2 = " + loop2);
		assert( loop2 < 10 );
	}

	return count == 10;
}

private bool TestCase3() const {
	int count;

	for ( int loop3 = 0; loop3 < 5; loop3 += 1 ) {
		print("loop3 = " + loop3);
		assert( loop3 < 5 );

		if ( loop3 > 2 ) {
			break;
		}

		count++;
	}

	print("count = " + count);

	return count == 3;
}

private bool TestCase4() const {
	for ( int loop4 = 0; loop4 < 10; loop4 += 1 ) {
		print("loop4 = " + loop4);

		if ( loop4 > 2 ) {
			return true;
		}
	}

	return false;
}

private bool TestCase5() const {
	print("TestCase 5: continue");

	for ( int loop5 = 0; loop5 < 10; loop5 += 1 ) {
		if ( loop5 == 2 ) {
			continue;
		}

		if ( loop5 == 4 ) {
			return true;
		}
	}

	return false;
}

private bool TestCase6() {
	print("TestCase 6: for ( ; <condition>; <expression> )");

	int i = 0;
	for ( ; i < 5; i += 1 ) {
		print("" + i + ": for loop without initialization");
	}

	return i == 5;
}

private bool TestCase7() {
	print("TestCase 7: for ( <initialization>; ; <expression> )");

	int count;

	for ( int i = 0; ; i++ ) {
		print("" + i + ": for loop without condition");

		if ( i == 5 ) {
			break;
		}

		count++;
	}

	return count == 5;
}

private bool TestCase8() {
	print("TestCase 8: for ( <initialization>; <condition>; )");

	int count;
	for ( int i = 0; i < 5; ) {
		print("" + i + ": for loop without expression");

		i++;
		count++;
	}

	return count == 5;
}

private bool TestCase9() const {
	print("TestCase 9: for ( ; ; )");

	int i = 0;
	for ( ; ; ) {
		print("" + i + ": for loop without condition");

		if ( i == 3 ) {
			break;
		}

		i++;
	}

	return true;
}

private bool TestCase10() const {
	print("TestCase 10: arbitrary iteration statement");

	for ( int i = 0; i < 5; { print((string i) + ": for loop with arbitrary iteration statement"); i++; } ) {
		// nothing to do here
	}

	return true;
}

