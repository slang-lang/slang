#!/usr/local/bin/oscript

public namespace ReturnTest
{
public object Main
{
public void Main(number argc, string argv)
{
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1()
{
	print("TestCase1()");
}

private bool TestCase2()
{
	print("TestCase2()");
	return;
}

}
}

