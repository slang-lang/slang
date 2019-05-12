
// Library imports
import System.Collections.IIterateable;
import System.IO.File;
import System.StringIterator;

// Project imports

public object Scanner implements IIterateable {
	public void Constructor(string filename) {
		mFile = new System.IO.File(filename, System.IO.FileAccessMode.ReadOnly);
		mSeparator = LINEBREAK;

		if ( mFile ) {
			readAll();
		}
	}

	public string getFilename() const {
		return mFile ? mFile.getFilename() : "";
	}

	public StringIterator getIterator() const {
		return new StringIterator(mText, mSeparator);
	}

	public string getText() const {
		return mText;
	}

	private void readAll() modify {
		mText = "";

		while ( !mFile.isEOF() ) {
			mText += mFile.readChar();
		}
	}

	private System.IO.File mFile;
	private string mSeparator;
	private string mText;
}

