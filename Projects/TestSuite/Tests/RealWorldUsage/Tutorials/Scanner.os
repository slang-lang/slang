
import System.Collections.IIterateable;
import System.IO.File;
import System.String;

public object Scanner implements IIterateable {
	private string mText;

	public void Constructor(System.IO.File file) {
		readAll(file);
	}

	private void readAll(System.IO.File file) {
		string ch;
		string word;

		while ( !file.isEOF() ) {
			ch = file.readString();

			word = word + ch;
		}

		print("word = " + word);
	}

	public StringIterator getIterator() const {
		return new StringIterator(mText, " ");
	}
}

