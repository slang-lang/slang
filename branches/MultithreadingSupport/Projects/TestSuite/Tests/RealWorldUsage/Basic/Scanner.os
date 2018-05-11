
import System.Collections.IIterateable;
import System.IO.File;
import System.StringIterator;

public object Scanner implements IIterateable {
	private System.IO.File mFile;
	private string mSeparator = " ";
	private string mText;

	public void Constructor(System.IO.File file ref, string separator) {
		mFile = file;
		mSeparator = separator;

		readAll(file);
	}

	public string getFilename() const {
		return mFile.getFilename();
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

