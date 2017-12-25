#!/usr/local/bin/oscript

public void Main(int argc = 0, string args = "") {
	int i = 1;

	assert( i is int );
	assert( 1 is int );
	//assert( 1i is int );	// integers followed by 'i' are not supported any more

	assert( !(1.f is int) );
	//assert( 1.f is int );

	print(typeid(1.0) == "double");
	print(typeid(1.f));
	print(typeid(!1.f));
	print(typeid((!1.f) is int));

	//assert( !1.f is int );
	//assert( (!1.f) is int );
	//assert( true is int );
}

