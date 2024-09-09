#!/usr/local/bin/slang

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );

	assert( TestCase11() );
	assert( TestCase12() );
	assert( TestCase13() );
	assert( TestCase14() );
}

private bool TestCase1() {
	print("TestCase 1: bool && !& !| ||");

	assert( true && true );
	assert( false !& false );
	assert( false !| false );
	assert( true || false );

	return true;
}

private bool TestCase2() {
	print("TestCase 2: double && !& !| ||");

	assert( 1.d && 1.d );
	assert( 0.d !& 0.d );
	assert( 0.d !| 0.d );
	assert( 0.d || 1.d );

	return true;
}

private bool TestCase3() {
	print("TestCase 3: float && !& !| ||");

	assert( 1.f && 1.f );
	assert( 0.f !& 1.f );
	assert( 0.f !| 1.f );
	assert( 0.d || 1.f );

	return true;
}

private bool TestCase4() {
	print("TestCase 4: int && !& !| ||");

	assert( 1 && 1 );
	assert( 0 !& 1 );
	assert( 0 !| 1 );
	assert( 0 || 1 );

	return true;
}

private bool TestCase5() {
	print("TestCase 5: string && !& !| ||");

	assert( "bla" && "haha" );
	assert( "" !& "haha" );
	assert( "" !| "haha" );
	assert( "" || "haha" );

	return true;
}

private bool TestCase11() {
	print("TestCase 11: bool && double && float && int && string");

	assert( true && 1.d && 1.f && 1 && "str" );

	return true;
}

private bool TestCase12() {
	return true;
}

private bool TestCase13() {
	return true;
}

private bool TestCase14() {
	print("TestCase 14: bool || double || float || int || string");

	assert( true || 1.d || 1.f || 1 || "str" );

	return true;
}

