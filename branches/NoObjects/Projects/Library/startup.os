
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

	private object Bla
	{
	}
	private Bla mBla;

	public void Main(/*string name, number value*/)
	{
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

		mBla = new Bla();
		print(mBla);
		assert(mBla);
	}

	public void ~Main()
	{
		mLogger.debug("Destructor");
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
}
