
private namespace Json {

public object StyledBuilder {
	// Consts
	private string INDENTATION const = "    ";

	// Members
	private int mIndentationLevel = 0;
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

		mIndentationLevel++;
		indent();

		mIsFirstElement = true;
		mValue += "[" + ascii(10);
	}

	public void beginArray(string key) modify {
		if ( !mIsFirstElement ) {
			mValue += ", " + ascii(10);
		}

		mIndentationLevel++;
		indent();

		mIsFirstElement = true;
		mValue += "\"" + key + "\": [" + ascii(10);
	}

	public void beginObject() modify {
		if ( !mIsFirstElement ) {
			mValue += ", " + ascii(10);
		}


		mIndentationLevel++;
		indent();

		mIsFirstElement = true;
		mValue += "{" + ascii(10);
	}

	public void beginObject(string key) modify {
		if ( !mIsFirstElement ) {
			mValue += ", " + ascii(10);
		}

		mIndentationLevel++;
		indent();

		mIsFirstElement = true;
		mValue += "\"" + key + "\": {" + ascii(10);
	}

	public void endArray() modify {
		mIndentationLevel--;
		indent();

		mIsFirstElement = false;
		mValue += "]";
	}

	public void endObject() modify {
		mIndentationLevel--;
		indent();

		mIsFirstElement = false;
		mValue += "}";
	}

	public string getString() const {
		return "{ " + ascii(10) + mValue + ascii(10) + " }";
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

