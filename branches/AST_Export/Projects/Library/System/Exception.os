
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object Exception {
	private string _exception;

	public void Constructor(string ex) {
		_exception = ex;
	}

	public string =operator(string none) const {
		return _exception;
	}

	public string what() const {
		return _exception;
	}
}

public object ArithmeticException extends Exception {
	public void Constructor(string ex) {
		base.Constructor("ArithmeticException: " + ex);
	}
}

public object IOException extends Exception {
	public void Constructor(string ex) {
		base.Constructor("IOException: " + ex);
	}
}

public object NullPointerException extends Exception {
	public void Constructor(string ex) {
		base.Constructor("NullPointerException: " + ex);
	}
}

public object OutOfBoundsException extends Exception {
	public void Constructor(string ex) {
		base.Constructor("OutOfBoundsException: " + ex);
	}
}

public object SecurityException extends Exception {
	public void Constructor(string ex) {
		base.Constructor("SecurityException: " + ex);
	}
}

