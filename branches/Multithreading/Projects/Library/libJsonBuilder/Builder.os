
private namespace Json {

public object Builder {
	private bool mIsFirstElement = true;
	private string mValue = "";

	public void addElement(string key, bool value) modify {
		if ( !mIsFirstElement ) {
			mValue += ", ";
		}

		mIsFirstElement = false;
		mValue += "\"" + key + "\": " + value;
	}

	public void addElement(string key, int value) modify {
		if ( !mIsFirstElement ) {
			mValue += ", ";
		}
	
		mIsFirstElement = false;
		mValue += "\"" + key + "\": " + value;
	}

	public void addElement(string key, string value) modify {
		if ( !mIsFirstElement ) {
			mValue += ", ";
		}

		mIsFirstElement = false;
		mValue += "\"" + key + "\": \"" + value + "\"";
	}

	public void beginArray() modify {
		if ( !mIsFirstElement ) {
			mValue += ", ";
		}

		mIsFirstElement = true;
		mValue += "[";
	}

	public void beginArray(string key) modify {
		if ( !mIsFirstElement ) {
			mValue += ", ";
		}

		mIsFirstElement = true;
		mValue += "\"" + key + "\": [";
	}

	public void beginObject() modify {
		if ( !mIsFirstElement ) {
			mValue += ", ";
		}

		mIsFirstElement = true;
		mValue += "{";
	}

	public void beginObject(string key) modify {
		if ( !mIsFirstElement ) {
			mValue += ", ";
		}

		mIsFirstElement = true;
		mValue += "\"" + key + "\": {";
	}

	public void endArray() modify {
		mIsFirstElement = false;
		mValue += "]";
	}

	public void endObject() modify {
		mIsFirstElement = false;
		mValue += "}";
	}

	public string getString() const {
		return "{ " + mValue + " }";
	}
}

}

