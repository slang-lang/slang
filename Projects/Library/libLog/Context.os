
// Library imports
import System.IO.File;

// Project imports
import IContext;


public object FileContext implements IContext {
	public void Constructor(string filename, bool append = false) {
		mFile = new System.IO.File(filename, append ? System.IO.File.AccessMode.WriteUpdate : System.IO.File.AccessMode.WriteOnly);
	}

	public void Destructor() {
		if ( mFile ) {
			mFile.close();
		}
	}

	public void write(string message) modify {
		mFile.write(message);
	}

	private System.IO.File mFile;
}

public object StdOutContext implements IContext {
	public void write(string message) modify {
		print(message);
	}
}

