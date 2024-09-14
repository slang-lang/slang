#!/usr/local/bin/slang

public object MethodWithWrongParameters {
	public static float calc(float value default) const {
		return value;
	}

	public static int calc(int value val) const {
		return value;
	}

	public static string calc(string value ref) const {
		return value;
	}
}

public void Main( int argc, string args ) {

	print( "Value: " + MethodWithWrongParameters.calc( 1.d ) );

}

