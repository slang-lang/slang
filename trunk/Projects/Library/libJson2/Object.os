
import Value;

public namespace Json {

public object Object extends Json.Value {
	public void Constructor() {
		base.Constructor();

		mType = Type.Object;
	}

	public void Constructor(string key, Json.Value value) {
		base.Constructor();

		mKey = key;
		mValue = value;
	}

	public string toString() const {
		return "{\"" + mKey + "\":" + (mValue ? mValue.toString() : "null") + "}";
	}

	private Json.Value mValue;
}

}

