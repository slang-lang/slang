#!/usr/bin/env slang

// Fazit: recursion is really slow in slang

public void Main(int argc, string args) {
	int value;

	if ( argc == 1 ) {
		//input to print Fibonacci series upto how many numbers
		cout("Enter number upto which Fibonacci series to print: ");
		value = cast<int>( cin() );
		endl();
	}
	else {
		value = cast<int>( substr( args, strfind( args, LINEBREAK ) ) );
	}

	cout("Fibonacci series upto " + value +" numbers: ");
	endl();

	//printing Fibonacci series upto number
	for ( int i = 1; i <= value; i++ ) {
		//cout("" + fibonacciRecusion(i) + " ");
		cout("" + fibonacciLoop(i) + " ");
	}
	endl();
} 

// slang program for Fibonacci number using recursion.
private int fibonacciRecusion(int value) {
	if ( value == 1 || value == 2 ) {
		return 1;
	}

	return fibonacciRecusion(value - 1) + fibonacciRecusion(value - 2); //tail recursion
}

// slang program for Fibonacci number using Loop.
private int fibonacciLoop(int value) {
	if ( value == 1 || value == 2 ) {
		return 1;
	}

	int fibo1 = 1;
	int fibo2 = 1;
	int fibonacci = 1;

	for ( int i = 3; i <= value; i++ ) {
		fibonacci = fibo1 + fibo2; //Fibonacci number is sum of previous two Fibonacci number
		fibo1 = fibo2;
		fibo2 = fibonacci;
	}

	return fibonacci; //Fibonacci number
}

