
// Library imports
import System.IO.File;

// Project imports
import IContext;


public object FileContext implements IContext {
	private System.IO.File mLogFile;

	public void Constructor(string filename) {
		mLogFile = new System.IO.File(filename, "w+");
	}

	public void Destructor() {
		if ( mLogFile ) {
			mLogFile.close();
		}
	}

	public void write(string message) {
		mLogFile.write(message);
	}
}

public object StdOutContext implements IContext {
	public void write(string message) {
		print(message);
	}
}

