
import System.Collections.IIterateable;
import System.IO.File;
import System.String;
import System.StringIterator;

public object Scanner implements IIterateable {
	private string mSeparator = " ";
	private string mText;

	public void Constructor(System.IO.File file, string separator) {
		mSeparator = separator;

		readAll(file);
	}

	private void readAll(System.IO.File file) modify {
		string ch;
		string word;

		while ( !file.isEOF() ) {
			ch = file.readString();

			word = word + ch;
		}

		mText = word;
	}

	public StringIterator getIterator() const {
		return new StringIterator(mText, mSeparator);
	}
}
