#!/usr/local/bin/slang


public object ResourceGuard {
	public void Constructor(string res) {
		mResource = res;

		print("Acquire the " + mResource + ".");
	}

	public void Destructor() {
		print("Release the " + mResource + ".");
	}

	public string =operator(string) const {
		return mResource;
	}

	private string mResource;
}

public void Main(int argc, string args) {
	Method1();
	Method2();
}

private void Method1() {
	print("");
	print("Method1");

	var rg1 = new ResourceGuard("memoryBlock1");

	print("Before local scope");
	{
		var rg2 = new ResourceGuard("memoryBlock2");
	}
	print("After local scope");

	print("Before try-catch block");
	try {
		var rg3 = new ResourceGuard("memoryBlock3");
		throw "bad_alloc";
	}
	catch ( string e ) {
		print(e);
	}
	print("After try-catch-block");
}

private void Method2() {
	print("");
	print("Method2");

	var rg1 = new ResourceGuard("memoryBlock1");

	print("Before local scope");
	{
		var rg2 = new ResourceGuard("memoryBlock2");
	}
	print("After local scope");

	print("Before try-catch block");
	try {
		//var rg3 = new ResourceGuard("memoryBlock3");
		throw new ResourceGuard("memoryBlock3");
	}
	catch ( ResourceGuard e ) {
		print(string e);
		delete e;
		print("memleak");
	}
	print("After try-catch-block");
}

