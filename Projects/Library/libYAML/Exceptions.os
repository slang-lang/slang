

// Library imports
import System.Exception;

// Project imports


public namespace Yaml { }

public object YamlException const implements IException {
	public void Constructor( string msg ) {
		_ex = msg;
	}

	public string what() const {
		return _ex;
	}

	private string _ex const;
}

public object InvalidTypeException const implements IException {
	public void Constructor( string msg ) {
		_ex = msg;
	}

	public string what() const {
		return _ex;
	}

	private string _ex const;
}

