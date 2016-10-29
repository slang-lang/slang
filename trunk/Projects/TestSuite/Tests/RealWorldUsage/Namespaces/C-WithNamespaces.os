#!/usr/local/bin/oscript

import System.Integer;

private namespace This {

	public int mIntValue;
	public Integer mIntegerValue;	// this does not work because only blueprints get retyped after parsing
	public string mStringValue;

	public void Init() modify {
		print("Init()");

		mIntValue = ReturnOne();
		mIntegerValue = new Integer(ReturnOne());
		mStringValue = "has been initialized";
	}

	public int ReturnOne() modify {
		return 1;
	}

}

public int Main(int argc, string args) {
	print("blöa");

	This.Init();

	print(This.mStringValue);

	return 0;
}

