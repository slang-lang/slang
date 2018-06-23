
private namespace Json {

public object StyledBuilder {
	private bool mIsFirstElement = true;
	private string mValue = "";


	public void addElement(string key, bool value) modify {
		if ( !mIsFirstElement ) {
			mValue += ", " + ascii(10);
		}

		mIsFirstElement = false;
		mValue += "\"" + key + "\": " + value;
	}

	public void addElement(string key, int value) modify {
		if ( !mIsFirstElement ) {
			mValue += ", " + ascii(10);
		}
	
		mIsFirstElement = false;
		mValue += "\"" + key + "\": " + value;
	}

	public void addElement(string key, string value) modify {
		if ( !mIsFirstElement ) {
			mValue += ", " + ascii(10);
		}

		mIsFirstElement = false;
		mValue += "\"" + key + "\": \"" + value + "\"";
	}

	public void beginArray() modify {
		mIsFirstElement = true;

		mValue += "[" + ascii(10);
	}

	public void beginArray(string key) modify {
		if ( !mIsFirstElement ) {
			mValue += ", " + ascii(10);
		}

		mIsFirstElement = true;
		mValue += "\"" + key + "\": [" + ascii(10);
	}

	public void beginObject() modify {
		if ( !mIsFirstElement ) {
			mValue += ", " + ascii(10);
		}

		mIsFirstElement = true;
		mValue += "{" + ascii(10);
	}

	public void beginObject(string key) modify {
		if ( !mIsFirstElement ) {
			mValue += ", " + ascii(10);
		}

		mIsFirstElement = true;
		mValue += "\"" + key + "\": {" + ascii(10);
	}

	public void endArray() modify {
		mIsFirstElement = false;
		mValue += "]" + ascii(10);
	}

	public void endObject() modify {
		mIsFirstElement = false;
		mValue += "}" + ascii(10);
	}

	public string getString() const {
		return "{ " + ascii(10) + mValue + ascii(10) + " }";
	}
}

}

