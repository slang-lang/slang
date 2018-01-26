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

public void Main(int argc, string args) {
        var params = new List<String>();

        foreach ( string p : String(args) ) {
                params.push_back(new String(p));
        }

        if ( params.size() < 2 ) {
                print("not enought parameters provided!");
                return;
        }

	foreach ( string line : new Scanner(new System.IO.File(string params.at(1), "r"), ascii(10)) ) {
		print(line);
	}
}

