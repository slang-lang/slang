
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public stable interface IException {
	public string what() const;
}

public object Exception implements IException {
	private string _exception;

	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}
}

public object ArithmeticException implements IException {
	private string _exception;

	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}
}

public object InvalidLengthException implements IException {
	private string _exception;

	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}
}

public object IOException implements IException {
	private string _exception;

	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}
}

public object NotInitializedException implements IException {
	private string _exception;

	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}
}

public object NullPointerException implements IException {
	private string _exception;

	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}
}

public object OutOfBoundsException implements IException {
	private string _exception;

	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}
}

public object SecurityException implements IException {
	private string _exception;

	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}
}

