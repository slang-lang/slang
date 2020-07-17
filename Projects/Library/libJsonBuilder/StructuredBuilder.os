
private namespace Json {

private bool mIsFirstElement = true;
private string mValue = "";


public void AddElement(string key, bool value) {
	if ( !mIsFirstElement ) {
		mValue += ", ";
	}

	mIsFirstElement = false;
	mValue += "\"" + key + "\": " + value;
}

public void AddElement(string key, int value) {
	if ( !mIsFirstElement ) {
		mValue += ", ";
	}

	mIsFirstElement = false;
	mValue += "\"" + key + "\": " + value;
}

public void AddElement(string key, string value) {
	if ( !mIsFirstElement ) {
		mValue += ", ";
	}

	mIsFirstElement = false;
	mValue += "\"" + key + "\": \"" + value + "\"";
}

public void AddValue(bool value) {
	if ( !mIsFirstElement ) {
		mValue += ", ";
	}

	mIsFirstElement = false;
	mValue += value;
}

public void AddValue(int value) {
	if ( !mIsFirstElement ) {
		mValue += ", ";
	}

	mIsFirstElement = false;
	mValue += value;
}

public void AddValue(string value) {
	if ( !mIsFirstElement ) {
		mValue += ", ";
	}

	mIsFirstElement = false;
	mValue += "\"" + value + "\"";
}

public void AddObject(string value) {
	if ( !mIsFirstElement ) {
		mValue += ", ";
	}

	mIsFirstElement = false;
	mValue += value;
}

public void BeginArray() {
	if ( !mIsFirstElement ) {
		mValue += ", ";
	}

	mIsFirstElement = true;
	mValue += "[";
}

public void BeginArray(string key) {
	if ( !mIsFirstElement ) {
		mValue += ", ";
	}

	mIsFirstElement = true;
	mValue += "\"" + key + "\": [";
}

public void BeginObject() {
	if ( !mIsFirstElement ) {
		mValue += ", ";
	}

	mIsFirstElement = true;
	mValue += "{";
}

public void BeginObject(string key) {
	if ( !mIsFirstElement ) {
		mValue += ", ";
	}

	mIsFirstElement = true;
	mValue += "\"" + key + "\": {";
}

public void EndArray() {
	mIsFirstElement = false;
	mValue += "]";
}

public void EndObject() {
	mIsFirstElement = false;
	mValue += "}";
}

public string GetString() {
	return "{ " + mValue + " }";
}

}

