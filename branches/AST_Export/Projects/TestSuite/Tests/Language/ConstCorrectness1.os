#!/usr/local/bin/oscript

private int mNumber;

public void Main(int argc const = 0, string argv const = "") modify {
	mNumber = 0;
	int one = 0;
	ModifyByValueParameter(one);
	assert( mNumber == 1 );
	assert( one == 0 );

	mNumber = 0;
	one = new int(0);
	ModifyByReferenceParameter(one);
	assert( mNumber == 1 );
	assert( one == 1 );

	mNumber = 0;
	int two const = 0;
	ModifyConstParameter(two);
	assert( false );
	assert( mNumber == 2 );
	assert( one == 0 );

	mNumber = 0;
	int three = 0;
	ModifyMemberInConstMethod(three);
	assert( false );
	assert( mNumber == 0 );
	assert( three == 0 );
}

private void ModifyByReferenceParameter(int value ref) modify {
	mNumber = 1;		// valid
	value = 1;		// valid
}

private void ModifyByValueParameter(int value val) modify {
	mNumber = 1;		// valid
	value = 1;		// valid, but argh...
}

private void ModifyConstParameter(int constValue const) modify {
	mNumber = 2;		// valid
	constValue = 2;		// invalid, throws a ConstCorrectnessViolated exception
	
	assert( false );
}

private void ModifyMemberInConstMethod(int value const) const {
	mNumber = value;	// invalid, throws a ConstCorrectnessViolated exception
	value = 2;		// invalid, throws a ConstCorrectnessViolated exception
	
	assert( false );
}

