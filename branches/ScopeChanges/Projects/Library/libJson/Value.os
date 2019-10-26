
// Library imports

// Project imports
import Array;
import Exceptions;
import Object;


public enum JsonType {
	Array,
	Object,
	Value
	;
}

public enum JsonValueType {
	Bool,
	Null,
	Number,
	Object,
	String
	;
}


public object JsonValue {
// Public
	public void Constructor() {
		mNumberValue = 0;
		mStringValue = "null";
		mValueType = JsonValueType.Null;
	}

	public void Constructor(bool value) {
		setValue(value);
	}

	public void Constructor(double value) {
		setValue(value);
	}

	public void Constructor(float value) {
		setValue(value);
	}

	public void Constructor(int value) {
		setValue(value);
	}

	public void Constructor(string value) {
		setValue(value);
	}

	public void Constructor(JsonArray array) {
		setValue(JsonValue array);
	}

	public void Constructor(JsonObject obj) {
		setValue(JsonValue obj);
	}

	public bool asBool() const {
		if ( mValueType == JsonValueType.Object ) {
			return bool mObjectValue;
		}
		else if ( mValueType == JsonValueType.String ) {
			return bool mStringValue;
		}

		return bool mNumberValue;
	}

	public double asDouble() const throws {
		if ( mValueType == JsonValueType.Object
		  || mValueType == JsonValueType.String ) {
			throw new InvalidTypeException();
		}

		return double mNumberValue;
	}

	public float asFloat() const throws {
		if ( mValueType == JsonValueType.Object
		  || mValueType == JsonValueType.String ) {
			throw new InvalidTypeException();
		}

		return float mNumberValue;
	}

	public int asInt() const throws {
		if ( mValueType == JsonValueType.Object
		  || mValueType == JsonValueType.String ) {
			throw new InvalidTypeException();
		}

		return int mNumberValue;
	}

	public string asString() const {
		if ( mValueType == JsonValueType.Object ) {
			return mObjectValue.asString();
		}
		else if ( mValueType == JsonValueType.String ) {
			return "\"" + mStringValue + "\"";
		}

		return string mNumberValue;
	}

	public JsonType getType() const {
		return mType;
	}

	public JsonValueType getValueType() const {
		return mValueType;
	}

	public bool isBool() const {
		return mValueType == JsonValueType.Bool;
	}

	public bool isNull() const {
		return mValueType == JsonValueType.Null;
	}

	public bool isNumber() const {
		return mValueType == JsonValueType.Number;
	}

	public bool isString() const {
		return mValueType == JsonValueType.String;
	}

	public void setValue(bool value) modify {
		mNumberValue = value;
		mObjectValue = JsonValue null;
		mStringValue = "";
		mType = JsonType.Value;
		mValueType = JsonValueType.Bool;
	}

	public void setValue(double value) modify {
		mNumberValue = value;
		mObjectValue = JsonValue null;
		mStringValue = "";
		mType = JsonType.Value;
		mValueType = JsonValueType.Number;
	}

	public void setValue(float value) modify {
		mNumberValue = value;
		mObjectValue = JsonValue null;
		mStringValue = "";
		mType = JsonType.Value;
		mValueType = JsonValueType.Number;
	}

	public void setValue(int value) modify {
		mNumberValue = value;
		mObjectValue = JsonValue null;
		mStringValue = "";
		mType = JsonType.Value;
		mValueType = JsonValueType.Number;
	}

	public void setValue(string value) modify {
		mNumberValue = 0;
		mObjectValue = JsonValue null;
		mStringValue = value;
		mType = JsonType.Value;
		mValueType = JsonValueType.String;
	}

	public void setValue(JsonValue value) modify {
		mNumberValue = 0;
		mObjectValue = value;
		mStringValue = "";
		mType = value.getType();
		mValueType = value.getValueType();
	}

	public int size() const {
		return 0;
	}

	public string toString() const {
		return asString();
	}

	public bool operator=(bool value) modify {
		setValue(value);

		return value;
	}

	public double operator=(double value) modify {
		setValue(value);

		return value;
	}

	public float operator=(float value) modify {
		setValue(value);

		return value;
	}

	public int operator=(int value) modify {
		setValue(value);

		return value;
	}

	public string operator=(string value) modify {
		setValue(value);

		return value;
	}

	public JsonArray operator=(JsonArray value) modify {
		setValue(JsonValue value);

		return JsonArray mObjectValue;
	}

	public JsonObject operator=(JsonObject value) modify {
		setValue(JsonValue value);

		return JsonObject mObjectValue;
	}

	public JsonValue operator=(JsonValue value) modify {
		setValue(value);

		return this;
	}

// Protected
	protected double mNumberValue;
	protected JsonValue mObjectValue;
	protected string mStringValue;
	protected JsonType mType;
	protected JsonValueType mValueType;
}

