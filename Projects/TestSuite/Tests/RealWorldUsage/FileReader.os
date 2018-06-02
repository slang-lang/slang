#!/usr/local/bin/oscript

import System.Collections.List;
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

public void Main(int argc, string args) {
	if ( argc < 2 ) {
		print("usage: program [arg1 [arg2 [...] ] ]");
		return;
	}

	var params = new List<String>();
	foreach ( string p : String(args) ) {
		params.push_back(new String(p));
	}

	for ( int idx = 1; idx < argc; idx++ ) {
		string filename = string params.at(idx);

		print(filename + ":");

		foreach ( string line : new Scanner(new System.IO.File(filename, "r"), ascii(10)) ) {
			print(line);
		}
	}
}

