
private namespace Json {

public object StyledBuilder {
	// Consts
	private string INDENTATION const = "    ";

	// Members
	private int mIndentationLevel = 1;
	private bool mIsFirstElement = true;
	private string mValue = "";


	public void addElement(string key, bool value) modify {
		if ( !mIsFirstElement ) {
			mValue += ", " + ascii(10);
		}

		indent();

		mIsFirstElement = false;
		mValue += "\"" + key + "\": " + value;
	}

	public void addElement(string key, double value) modify {
		if ( !mIsFirstElement ) {
			mValue += ", " + ascii(10);
		}

		indent();

		mIsFirstElement = false;
		mValue += "\"" + key + "\": " + value;
	}

	public void addElement(string key, float value) modify {
		if ( !mIsFirstElement ) {
			mValue += ", " + ascii(10);
		}

		indent();

		mIsFirstElement = false;
		mValue += "\"" + key + "\": " + value;
	}

	public void addElement(string key, int value) modify {
		if ( !mIsFirstElement ) {
			mValue += ", " + ascii(10);
		}

		indent();

		mIsFirstElement = false;
		mValue += "\"" + key + "\": " + value;
	}

	public void addElement(string key, string value) modify {
		if ( !mIsFirstElement ) {
			mValue += ", " + ascii(10);
		}

		indent();

		mIsFirstElement = false;
		mValue += "\"" + key + "\": \"" + value + "\"";
	}

	public void beginArray() modify {
		if ( !mIsFirstElement ) {
			mValue += ", " + ascii(10);
		}

		indent();

		mIndentationLevel++;
		mIsFirstElement = true;
		mValue += "[" + ascii(10);
	}

	public void beginArray(string key) modify {
		if ( !mIsFirstElement ) {
			mValue += ", " + ascii(10);
		}

		indent();

		mIndentationLevel++;
		mIsFirstElement = true;
		mValue += "\"" + key + "\": [" + ascii(10);
	}

	public void beginObject() modify {
		if ( !mIsFirstElement ) {
			mValue += ", " + ascii(10);
		}

		indent();

		mIndentationLevel++;
		mIsFirstElement = true;
		mValue += "{" + ascii(10);
	}

	public void beginObject(string key) modify {
		if ( !mIsFirstElement ) {
			mValue += ", " + ascii(10);
		}

		indent();

		mIndentationLevel++;
		mIsFirstElement = true;
		mValue += "\"" + key + "\": {" + ascii(10);
	}

	public void endArray() modify {
		mIndentationLevel--;
		mIsFirstElement = false;
		mValue += ascii(10);
		indent();
		mValue += "]";
	}

	public void endObject() modify {
		mIndentationLevel--;
		mIsFirstElement = false;
		mValue += ascii(10);
		indent();
		mValue += "}";
	}

	public string getString() const {
		return "{" + ascii(10) + mValue + ascii(10) + "}" + ascii(10);
	}

	private void indent() modify {
		int c;
		while ( c < mIndentationLevel ) {
			mValue += INDENTATION;
			c++;
		}
	}
}

}

