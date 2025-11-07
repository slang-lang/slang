#!/usr/bin/env slang

public object TestObject
{
    public int Value = 173;

    public string toString() const {
        return streval( "Value: {{{Value}}}" );
    }
}

public void Main(int argc = 1, string args = "") {
	int value = 3;

	var stringEval = streval("Hello, {{{value}}} World!");
	print(stringEval);

	var testObject = new TestObject();
	print(streval("Hello, {{{testObject.Value}}} World!"));
	print( testObject.toString() );

	assert(stringEval == "Hello, 3 World!");
}
