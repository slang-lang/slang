#!/usr/local/bin/oscript

import System.Double;

public object Main {

	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
		//assert( TestCase2() );

		//assert(!"not implemented");
	}

	private bool TestCase1() modify {
		Double value = new Double();

		assert( !value.Value() );

		value.Value(double 1);
		assert( value.Value() );

		return true;
	}

	private bool TestCase2() const {
		assert( false );
		return false;
	}

}

