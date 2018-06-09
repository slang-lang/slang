
private namespace Json {

public object Builder {
	private bool mIsFirstElement = true;
	private string mValue = "";


	public void AddElement(string key, bool value) modify {
		if ( !mIsFirstElement ) {
			mValue += ", ";
		}

		mIsFirstElement = false;
		mValue += "\"" + key + "\": " + value;
	}

	public void AddElement(string key, int value) modify {
		if ( !mIsFirstElement ) {
			mValue += ", ";
		}
	
		mIsFirstElement = false;
		mValue += "\"" + key + "\": " + value;
	}

	public void AddElement(string key, string value) modify {
		if ( !mIsFirstElement ) {
			mValue += ", ";
		}

		mIsFirstElement = false;
		mValue += "\"" + key + "\": \"" + value + "\"";
	}

	public void BeginArray() modify {
		mIsFirstElement = true;

		mValue += "[";
	}

	public void BeginArray(string key) modify {
		if ( !mIsFirstElement ) {
			mValue += ", ";
		}

		mIsFirstElement = true;
		mValue += "\"" + key + "\": [";
	}

	public void BeginObject() modify {
		mIsFirstElement = true;

		mValue += "{";
	}

	public void BeginObject(string key) modify {
		if ( !mIsFirstElement ) {
			mValue += ", ";
		}

		mIsFirstElement = true;
		mValue += "\"" + key + "\": {";
	}

	public void EndArray() modify {
		mIsFirstElement = false;
		mValue += "]";
	}

	public void EndObject() modify {
		mIsFirstElement = false;
		mValue += "}";
	}

	public string GetString() const {
		return "{ " + mValue + " }";
	}
}

}

