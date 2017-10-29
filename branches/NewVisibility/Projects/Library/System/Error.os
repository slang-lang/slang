
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object Error {
	private string _error;

	public void Constructor(string error) {
		_error = error;
	}

	public string what() const {
		return _error;
	}
}

public object IdentifierNotFoundError extends Error {
	public void Constructor(string error) {
		base.Constructor("IdentifierNotFound: " + error);
	}
}

public object MethodNotFoundError extends Error {
	public void Constructor(string error) {
		base.Constructor("MethodNotFound: " + error);
	}
}

