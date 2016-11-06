#!/usr/local/bin/oscript

import System.Assert;
import System.IO.Logger;
import System.String;

public object BaseObject {
	private System.IO.Logger mLogger;
	protected string mName;

	public void constMethod() const {
		mName = "this should not be possible";
		assert(false);
	}

	public void staticMethod() static {
		mName = "this should not be possible";
		assert(false);
	}

	public void Constructor() {
		print("BaseObject()");

		mLogger = new System.IO.Logger("BaseObject");
		mName = "BaseObject";
	}

	public void Constructor(string name const) {
		print("BaseObject(" + name + ")");

		mLogger = new System.IO.Logger(name);
		mName = name;
	}

	public string getName() const {
		return mName;
	}

	public void setLogger(System.IO.Logger logger ref) modify {
		mLogger = logger;
	}

	public void setName(String name) modify {
		mName = name;
	}

	private void privateMethodCall() {
		mLogger.error("privateMethodCall()");
		//print("privateMethodCall()");
	}

	protected void protectedMethodCall() {
		mLogger.warning("protectedMethodCall()");
		//print("protectedMethodCall()");
	}

	public void publicMethodCall() {
		mLogger.debug("publicMethodCall()");
		//print("publicMethodCall()");
	}
}

/////////////////////////////////// Member Declarations \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

private BaseObject mBaseObject;
private System.IO.Logger mLogger;

private float mLastUpdate;
private string mName;
private float mValue;

/////////////////////////////////// Public Methods \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

public void Main(int argc, string argv) {
	print("Main(" + argc + ", \"" + argv + "\")");

//	mLogger = new System.IO.Logger("Main");
//	mLogger.info("Constructor");

	mBaseObject = new BaseObject("\"this is a test\"");
	//mBaseObject.setLogger(mLogger);
	//mBaseObject.constMethod();	// handled correctly
	//mBaseObject.privateMethodCall();
	//mBaseObject.protectedMethodCall();
	mBaseObject.publicMethodCall();
	//mBaseObject.staticMethod();	// access to members in static method is not yet handled correctly

	mName = "Main";
	mValue = 0.f;

	//assertmsg("failed", true);
}

public string getName() const {
	return mName;
}

public void setName(string name) modify {
	mName = name;
}

public void update(float elapsedTime) modify {
	mLastUpdate = elapsedTime;
}

public void test_scope() {
	string var = "outer";
	{
		string var = "inner";
		print(var);
	}
	print(var);
}

