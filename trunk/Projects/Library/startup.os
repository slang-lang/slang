
//import system.*;
import system.assert;
import system.logger;

public object BaseObject
{
	private Logger mLogger;
	protected String mName;

	public void constMethod() const
	{
		mName = "this should not be possible";
		assert(false);
	}

	public void staticMethod() static
	{
		mName = "this should not be possible";
		assert(false);
	}

	public void BaseObject()
	{
		mLogger = new Logger("BaseObject");
		mName = "BaseObject";
	}

	public void BaseObject(String name const)
	{
		mLogger = new Logger(name);
		mName = name;
	}

	public String getName() const
	{
		return mName;
	}

	public void setLogger(Logger l)
	{
		assert(false);
		mLogger = l;
	}

	public void setName(String name)
	{
//		mLogger.debug("setName(" & name & ")");

		mName = name;
	}

	private void privateMethodCall()
	{
//		mLogger.debug("privateMethodCall()");
		print("privateMethodCall()");
	}

	protected void protectedMethodCall()
	{
//		mLogger.debug("protectedMethodCall()");
		print("protectedMethodCall()");
	}

	public void publicMethodCall()
	{
		mLogger.debug("publicMethodCall()");
		print("publicMethodCall()");
	}
}

private object Main extends public BaseObject,
							private Logger
{
/////////////////////////////////// Member Declarations \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	private Assert mAssert;
	private BaseObject mBaseObject;
	private Logger mLogger;

	private Number mLastUpdate;
	private String mName;
	private Number mValue;

/////////////////////////////////// Public Methods \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

/*
	private object Bla
	{
	}
	private Bla mBla;
*/

	public void Main(/*string name, number value*/)
	{
	//	print("this is a constructor");

		mLogger = new Logger("Main");
		mLogger.debug("Constructor");


		mBaseObject = new BaseObject("this is a test");
/*	// handing over objects as parameters does not work right now because parameters are still variables instead of objects
		mBaseObject.setLogger(mLogger);
*/
		//mBaseObject.constMethod();	// handled correctly
		//mBaseObject.staticMethod();	// access to members in static method is not yet handled correctly

		mName = "Main";
		mValue = 0.0;

		mAssert.assertmsg("failed", true);
	}

	public void ~Main()
	{
	//	print("this is a destructor");
	}

	public String getName() const
	{
		return mName;
	}

	public void setName(String name)
	{
		mName = name;
	}

/*
	public void update(Number elapsedTime)
	{
		mLastUpdate = elapsedTime;
	}
*/

/////////////////////////////////// Test cases \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	public void test_assert()
	{
		assert(true);
		assert(incStaticVar());
		assert(incStaticVar() & "bla");
		assert(true == false);
	}

	public void test_comments(/*number param1*/)
	{
		//this is a single line comment
		// this is another single line comment
		/*this is a multi
			line comment*/
		/* this is another multi
			line comment */
		/*
		print("this will not be executed");
		*/
		print("this is /* not */ a comment");
	}

	public void test_executeMethod()
	{
//		mBaseObject.publicMethodCall();
//		mBaseObject.protectedMethodCall();
//		mBaseObject.privateMethodCall();

		returnVoid();

		Number i = 0;
		i = testMethod(
			returnNumber(1),
			returnNumber(2)
		);
		print("i = " & i);

		i = returnSum(2, 3);
		print("i = " & i);

		i = returnSum(3, 4, 5);
		print("i = " & i);

		i = returnSum("6+", "7");
		print("i = " & i);

		i = returnSum(""&8, "9");
		print("i = " & i);
	}

	public void test_for()
	{
		breakpoint;

		for ( Number i = 0; i < 5; i = i + 1 ) {
			print("i =" & i);
		}

		breakpoint;
	}

	public void test_if(Number param1)
	{
		breakpoint;
	/*
		if ( true ) {
			print("if: true");
		}
		if ( false ) {
			print("if: false");
		}
		else {
			print("if: else");
		}
	*/
		if ( param1 - 1 == 0 ) {
			print("if: true");
		}
		else if ( true ) {
			print("else: if: true");
		}
		else {
			print("else: if: else");
		}

		breakpoint;
	}

	public void test_localVar()
	{
		Number i = 1;
		print("print i = " & i); 
	}

	public void test_print(String param1)
	{
		print("print 'text' with single quotes");
		print("print \"text\" with double quotes");
		print("print text with numbers 1234567890");
		print("print text with special characters: ,.-;:_#'+*´`ß?");
		print(1 + 2);
		print(1 & param1 & 2);
	}

	public void test_staticLocalVar()
	{
		Number i = 0;

		i = incStaticVar();
		print("i = " & i);

		i = incStaticVar();
		print("i = " & i);

		i = incStaticVar();
		print("i = " & i);
	}

	public void test_while(Number maxCount)
	{
		breakpoint;

		Number count = 0;
		while ( count < maxCount ) {
			count = count + 1;
			print("count = " & count);
		}

		breakpoint;
	}

	/*
	public void test_scope()
	{
		string var = "outer";
		{
			string var = "inner";
			print(var);
		}
		print(var);
	}
	*/

/////////////////////////////////// Operator overloading \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	/*
	public number operator+(number other)
	{
		return mValue + other;
	}

	public number operator-(number other)
	{
		return mValue - other;
	}
	*/

/////////////////////////////////// Private Methods \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	private Number incStaticVar()
	{
		Number var static = 0;

		var = var + 1;
		
		return var;
	}

	private Number returnNumber(Number param1)
	{
		return param1;
	}

	private Number returnSum(Number p1, Number p2)
	{
		return p1 + p2;
	}

	private Number returnSum(Number p1, Number p2, Number p3)
	{
		return p1 + p2 + p3;
	}

	private String returnSum(String p1, String p2)
	{
		return p1 & p2;
	}

	private void returnVoid()
	{
		print("method without parameters called");
	}

	private Number testMethod(Number param1, Number param2)
	{
		return param1 + param2;
	}
}
