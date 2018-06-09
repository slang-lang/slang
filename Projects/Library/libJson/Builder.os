
private namespace Json {

public object JsonBuilder {
	private string mValue;

	public void Constructor(string value = "") {
		mValue = value;
	}

	public void addElement(string key, string value) modify {
		if ( mValue ) {
			mValue += ", ";
		}

		mValue += "\"" + key + "\": " + value;
	}

	public string getValue() const {
		return "{ " + mValue + " }";
	}
}

}

