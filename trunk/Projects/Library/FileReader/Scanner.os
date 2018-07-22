
// Library imports
import System.Collections.IIterateable;
import System.IO.File;
import System.StringIterator;

// Project imports

public object Scanner implements IIterateable {
	private System.IO.File mFile;
	private string mSeparator;
	private string mText;

	public void Constructor(System.IO.File file ref, string separator = " ") {
		mFile = file;
		mSeparator = separator;

		readAll();
	}

	public string getFilename() const {
		return mFile.getFilename();
	}

	public string getText() const {
		return mText;
	}

	private void readAll() modify {
		mText = "";

		string ch;

		while ( !mFile.isEOF() ) {
			ch = mFile.readChar();

			mText += ch;
		}
	}

	public StringIterator getIterator() const {
		return new StringIterator(mText, mSeparator);
	}
}

