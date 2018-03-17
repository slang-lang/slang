
// Library imports
import System.IO.File;

// Project imports
import IContext;


public object FileContext implements IContext {
	private System.IO.File mFile;

	public void Constructor(string filename) {
		mFile = new System.IO.File(filename, "w+");
	}

	public void Destructor() {
		if ( mFile ) {
			mFile.close();
		}
	}

	public void write(string message) modify {
		mFile.write(message);
	}
}

public object StdOutContext implements IContext {
	public void write(string message) modify {
		print(message);
	}
}

