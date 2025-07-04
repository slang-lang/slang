#!/usr/bin/env slang

public void Main(int argc = 0, string argv = "")
{
	assert(true);
	assert(false == false);
	assert(1);
	assert(ReturnOne());
	assert(ReturnOne() > 0);
	assert("bla" + ReturnOne() + "bla");
	assert(ReturnAString());
	assert(ReturnTrue());
	assert(!ReturnFalse());	// unary operator ! is not yet implemented
	assert(ReturnFalse());
}

private string ReturnAString() const
{
	return "ThisIsAString";
}

private int ReturnOne() const
{
	return 1;
}

private bool ReturnFalse() const
{
	return false;
}

private bool ReturnTrue() const
{
	return true;
}

