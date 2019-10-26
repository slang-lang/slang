
// Library imports
import System.Exception;

// Project imports


public object FatalError implements IException {
    public void Constructor(string message) {
        _message = message;
    }

    public string what() const {
        return _message;
    }

    private string _message;
}

