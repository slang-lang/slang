
// Library imports
import System.Exception;

// Project imports


public object FatalError const implements IException {
    public void Constructor(string msg) {
        message = msg;
    }

    public string what() const {
        return message;
    }

    private string message const;
}

