
// library imports
import System.CharacterIterator;
import System.Collections.IIterable;
import System.IO.File;

// project imports


public object Scanner implements IIterable {
	public void Constructor(System.IO.File file) {
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

		while ( !file.isEOF() ) {
			mText += file.readChar();
		}
	}

	private System.IO.File mFile;
	private string mText;
}

