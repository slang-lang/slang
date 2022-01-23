
// Library imports
import System.CharacterIterator;
import System.Collections.IIterable;
import System.IO.File;
import System.StringIterator;

// Project imports


public object Scanner implements IIterable {
	public void Constructor( string filename ) {
		mFile = new System.IO.File( filename, System.IO.File.AccessMode.ReadOnly );

		readFile();
	}

	public string getFilename() const {
		return mFile ? mFile.getFilename() : "";
	}

	public CharacterIterator getIterator() const {
		return new CharacterIterator( mText );
	}

	public StringIterator getStringIterator( string separator ) const {
		return new StringIterator( mText, separator );
	}

	public string getText() const {
		return mText;
	}

	public void reset() modify {
		mFile.rewind();
		mText = "";

		readFile();
	}

	private void readFile() modify {
		if ( mText ) {
			return;
		}

		while ( !mFile.isEOF() ) {
			mText += mFile.readChar();
		}
	}

	private System.IO.File mFile;
	private string mText;
}

