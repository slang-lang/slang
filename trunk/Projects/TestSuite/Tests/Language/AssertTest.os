#!/usr/local/bin/oscript

import system.assert;

public namespace
{
	private object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert(true);
			assert(false == false);
			assert(ReturnOne());
			assert(ReturnOne() > 0);
			assert("bla" + ReturnOne() + "bla");
			assert(ReturnAString());
			assert(ReturnTrue());
			//assert(!ReturnFalse());	// unary operator ! is not yet implemented
			assert(ReturnFalse());
		}

		private string ReturnAString() const
		{
			return "ThisIsAString";
		}

		private number ReturnOne() const
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
	}
}
