
// library imports
import System.Collections.IIterable;
import System.IO.File;
import System.StringIterator;

// project imports


public object Scanner implements IIterable {
	private System.IO.File mFile;
	private string mSeparator = " ";
	private string mText;

	public void Constructor(System.IO.File file ref, string separator) {
		mFile = file;
		mSeparator = separator;

		if ( mFile ) {
			readAll(file);
		}
	}

	public string getFilename() const {
		return mFile ? mFile.getFilename() : "";
	}

	public string getText() const {
		return mText;
	}

	private void readAll(System.IO.File file) modify {
		mText = "";

		string ch;

		while ( !file.isEOF() ) {
			ch = file.readChar();

			mText += ch;
		}
	}

	public StringIterator getIterator() const {
		return new StringIterator(mText, mSeparator);
	}
}

