

// Library imports
import System.Exception;

// Project imports


public object JsonException implements IException {
	public void Constructor(string msg) {
		_ex = msg;
	}

	public string what() const {
		return _ex;
	}

	private string _ex;
}

public object InvalidTypeException implements IException {
	private string _ex;

	public void Constructor(string msg) {
		_ex = msg;
	}

	public string what() const {
		return _ex;
	}
}

