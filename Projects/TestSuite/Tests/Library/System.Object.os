#!/usr/local/bin/oscript

import System.Object;

public object IObjectImplementation implements /*System.*/IObject {

	public void IObjectImplementation() {
	}
	
	public string GetObjectType() const {
		return "IObjectImplementation";
	}
	
	public string ToString() const {
		return "IObjectImplementation.ToString()";
	}

}

public object TObjectDerivate extends /*System.*/TObject {

	public string ToString() const {
		return "TObjectDerivate.ToString()";
	}

}

public object Main {
	public void Main(int argc, string args) {
		assert( TestCase1() );
		assert( TestCase2() );
	}

	public bool TestCase1() const {
		IObjectImplementation obj = new IObjectImplementation();

		print(obj.ToString());

		return obj;
	}

	public bool TestCase2() const {
		TObjectDerivate obj = new TObjectDerivate();

		print(obj.ToString());

		return obj;
	}
}
