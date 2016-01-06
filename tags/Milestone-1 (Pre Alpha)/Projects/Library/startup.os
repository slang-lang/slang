#!/usr/local/bin/oscript

//import system.*;
import system.assert;
import system.logger;

public object BaseObject
{
	private Logger mLogger;
	protected string mName;

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

	public void BaseObject(string name const)
	{
		mLogger = new Logger(name);
		mName = name;
	}

	public string getName() const
	{
		return mName;
	}

	public void setLogger(Logger logger ref) modify
	{
		mLogger = logger;
	}

	public void setName(String name) modify
	{
//		mLogger.debug("setName(" + name + ")");

		mName = name;
	}

	private void privateMethodCall()
	{
		mLogger.debug("privateMethodCall()");
		print("privateMethodCall()");
	}

	protected void protectedMethodCall()
	{
		mLogger.debug("protectedMethodCall()");
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

	private number mLastUpdate;
	private string mName;
	private number mValue;

/////////////////////////////////// Public Methods \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	private object Bla
	{
	}
	private Bla mBla;

	public void Main(number argc, string argv)
	{
		mLogger = new Logger("Main");
		mLogger.debug("Constructor");


		mBaseObject = new BaseObject("this is a test");
		mBaseObject.setLogger(mLogger);
		mBaseObject.constMethod();	// handled correctly
		mBaseObject.staticMethod();	// access to members in static method is not yet handled correctly

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

	public string getName() const
	{
		return mName;
	}

	public void setName(string name) modify
	{
		mName = name;
	}

	public void update(number elapsedTime) modify
	{
		mLastUpdate = elapsedTime;
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
}
