
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public stable interface IException {
	public string what() const;
}

public object Exception const implements IException {
	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}

	private string _exception const;
}

public object ArithmeticException const implements IException {
	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}

	private string _exception const;
}

public object InvalidArgumentException const implements IException {
	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}

	private string _exception const;
}

public object InvalidLengthException const implements IException {
	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}

	private string _exception const;
}

public object IOException const implements IException {
	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}

	private string _exception const;
}

public object NotInitializedException const implements IException {
	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}

	private string _exception const;
}

public object NullPointerException const implements IException {
	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}

	private string _exception const;
}

public object OutOfBoundsException const implements IException {
	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}

	private string _exception const;
}

public object SecurityException const implements IException {
	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}

	private string _exception const;
}

