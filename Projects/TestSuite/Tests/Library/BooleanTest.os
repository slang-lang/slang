#!/usr/local/bin/oscript

import System.Boolean;

public object Main {

	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
		assert( TestCase2() );
	}

	private bool TestCase1() const {
		// default value is false
		Boolean value = new Boolean();

		return value;
	}

	private bool TestCase2() const {
		

		return true;
	}

}

