
// library imports
import System.Collections.IIterateable;
import System.IO.File;
import System.CharacterIterator;

// project imports


public object Scanner implements IIterateable {
	public void Constructor(System.IO.File file ref) {
		if ( file ) {
			mFile = file;

			readAll(mFile);
		}
	}

	public string getFilename() const {
		return mFile ? mFile.getFilename() : "";
	}

	public CharacterIterator getIterator() const {
		return new CharacterIterator(mText);
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

	private System.IO.File mFile;
	private string mText;
}

