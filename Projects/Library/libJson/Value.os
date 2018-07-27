
// Library imports

// Project imports
import Exceptions;
import Object;


public namespace Json {

	public enum Type {
		Array,
		Object,
		Value
		;
	}

	public enum ValueType {
		Bool,
		Double,
		Float,
		Int,
		Object,
		String
		;
	}

}

public object JsonValue {
// Public
	public void Constructor() {
		mNumberValue = 0;
		mStringValue = "null";
		mValueType = Json.ValueType.Object;
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
		if ( mValueType == Json.ValueType.Object ) {
			return bool mObjectValue;
		}
		else if ( mValueType == Json.ValueType.String ) {
			return bool mStringValue;
		}

		return bool mNumberValue;
	}

	public double asDouble() const throws {
		if ( mValueType == Json.ValueType.Object
		  || mValueType == Json.ValueType.String ) {
			throw new InvalidTypeException();
		}

		return double mNumberValue;
	}

	public float asFloat() const throws {
		if ( mValueType == Json.ValueType.Object
		  || mValueType == Json.ValueType.String ) {
			throw new InvalidTypeException();
		}

		return float mNumberValue;
	}

	public int asInt() const throws {
		if ( mValueType == Json.ValueType.Object
		  || mValueType == Json.ValueType.String ) {
			throw new InvalidTypeException();
		}

		return int mNumberValue;
	}

	public string asString() const {
		if ( mValueType == Json.ValueType.Object ) {
			return mObjectValue.asString();
		}
		else if ( mValueType == Json.ValueType.String ) {
			return "\"" + mStringValue + "\"";
		}

		return string mNumberValue;
	}

	public Json.Type getType() const {
		return mType;
	}

	public Json.ValueType getValueType() const {
		return mValueType;
	}

	public bool isBool() const {
		return mValueType == Json.ValueType.Bool;
	}

	public bool isDouble() const {
		return mValueType == Json.ValueType.Double;
	}

	public bool isFloat() const {
		return mValueType == Json.ValueType.Float;
	}

	public bool isInt() const {
		return mValueType == Json.ValueType.Int;
	}

	public bool isString() const {
		return mValueType == Json.ValueType.String;
	}

	public void setValue(bool value) modify {
		mNumberValue = value;
		mObjectValue = JsonValue null;
		mStringValue = "";
		mType = Json.Type.Value;
		mValueType = Json.ValueType.Bool;
	}

	public void setValue(double value) modify {
		mNumberValue = value;
		mObjectValue = JsonValue null;
		mStringValue = "";
		mType = Json.Type.Value;
		mValueType = Json.ValueType.Double;
	}

	public void setValue(float value) modify {
		mNumberValue = value;
		mObjectValue = JsonValue null;
		mStringValue = "";
		mType = Json.Type.Value;
		mValueType = Json.ValueType.Float;
	}

	public void setValue(int value) modify {
		mNumberValue = value;
		mObjectValue = JsonValue null;
		mStringValue = "";
		mType = Json.Type.Value;
		mValueType = Json.ValueType.Int;
	}

	public void setValue(string value) modify {
		mNumberValue = 0;
		mObjectValue = JsonValue null;
		mStringValue = value;
		mType = Json.Type.Value;
		mValueType = Json.ValueType.String;
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
	protected Json.Type mType;
	protected Json.ValueType mValueType;
}

