#!/usr/local/bin/oscript

import System.Exception;
import System.IO.File;

public object TestObject {
	private string mName;
	private int mType;

	public void TestObject() {
		mName = "";
		mType = 0;
	}

	public void TestObject(string name, int type) {
		mName = name;
		mType = type;
	}
}

public object DerivedObject extends TestObject {
	private bool mFlag;

	public void DerivedObject() {
		base.TestObject();

		mFlag = false;
	}

	public void DerivedObject(string name, int type, bool flag) {
		base.TestObject(name, type);

		mFlag = flag;
	}
}

public object ExtendedObject extends DerivedObject {
	private float mFloat;
}

public object Main
{
	public void Main(int argc, string argv) {
		assert( TestCase1() );
		assert( TestCase2() );
		assert( TestCase3() );
		assert( TestCase4() );
	}

	private bool TestCase1() const {
		writeln("TestCase 1");

		Test_ToJson();
		Test_FromJson();

		writeln("");

		return true;
	}

	private bool TestCase2() const {
		writeln("TestCase 2");

		TestObject test = new TestObject("MeinName", 1731389);

		string json = ToJsonString(Object test);
		writeln("json = " + json);

		TestObject obj2;
		FromJsonString(Object obj2, json);

		writeln("obj2={" + obj2.mName + "," + obj2.mType + "}");

		writeln("");

		return true;
	}

	private bool TestCase3() const {
		writeln("TestCase 3");

		Exception ex = new System.Exception("this is an exception");

		writeln(ToJsonString(Object ex));

		File file;
		writeln(ToJsonString(Object file));

		writeln("");

		return true;
	}

	private bool TestCase4() const {
		writeln("TestCase 4");

		DerivedObject derived = new DerivedObject("derived", 173, true);

		string json = ToJsonString(Object derived);
		writeln("json = " + json);

		DerivedObject generated;
		FromJsonString(Object generated, json);

		writeln("generated={" + generated.mName + "," + generated.mType + "," + generated.mFlag + "}");

		writeln("");

		return true;
	}

	private bool Test_FromJson() const {
		TestObject obj = new TestObject();
		FromJsonString(Object obj, "{ \"mName\": \"test\" }");

		writeln("obj={" + obj.mName + "," + obj.mType + "}");

		return true;
	}

	private bool Test_ToJson() const {
		TestObject obj = new TestObject("test", 17);

		writeln("ToJson(obj) = " + ToJsonString(Object obj));

		return true;
	}
}
