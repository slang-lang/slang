
// Library imports
import System.Exception;


public object FatalError implements IException {
    private string _message;

    public void Constructor(string message) {
        _message = message;
    }

    public string what() const {
        return _message;
    }
}

