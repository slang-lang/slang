
// Library imports

// Project imports
import Exceptions;


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
		Nil,
		String
		;
	}

}

public object JsonValue {
// Public
	public void Constructor() {
		mNumberValue = 0;
		mStringValue = "null";
		mValueType = Json.ValueType.Nil;
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

	public bool asBool() const {
		if ( mValueType == Json.ValueType.String ) {
			return bool mStringValue;
		}

		return bool mNumberValue;
	}

	public double asDouble() const throws {
		if ( mValueType == Json.ValueType.String ) {
			throw new InvalidTypeException();
		}

		return double mNumberValue;
	}

	public float asFloat() const throws {
		if ( mValueType == Json.ValueType.String ) {
			throw new InvalidTypeException();
		}

		return float mNumberValue;
	}

	public int asInt() const throws {
		if ( mValueType == Json.ValueType.String ) {
			throw new InvalidTypeException();
		}

		return int mNumberValue;
	}

	public string asString() const {
		if ( mValueType == Json.ValueType.String ) {
			return mStringValue;
		}

		return string mNumberValue;
	}

	public string getKey() const {
		return mKey;
	}

	public Json.Type getType() const {
		return mType;
	}

	public Json.ValueType getValueType() const {
		return mValueType;
	}

	public bool isString() const {
		return mValueType == Json.ValueType.String;
	}

	public void setValue(bool value) modify {
		mNumberValue = value;
		mType = Json.Type.Value;
		mValueType = Json.ValueType.Bool;
	}

	public void setValue(double value) modify {
		mNumberValue = value;
		mType = Json.Type.Value;
		mValueType = Json.ValueType.Double;
	}

	public void setValue(float value) modify {
		mNumberValue = value;
		mType = Json.Type.Value;
		mValueType = Json.ValueType.Float;
	}

	public void setValue(int value) modify {
		mNumberValue = value;
		mType = Json.Type.Value;
		mValueType = Json.ValueType.Int;
	}

	public void setValue(string value) modify {
		mStringValue = value;
		mType = Json.Type.Value;
		mValueType = Json.ValueType.String;
	}

	public string toString() const {
		if ( mValueType == Json.ValueType.String ) {
			return "\"" + mStringValue + "\"";
		}

		return string mNumberValue;
	}

	public JsonValue operator=(JsonValue value) modify {
		mKey = value.getKey();
		mType = value.getType();

		return this;
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

// Protected
	protected string mKey const;
	protected Json.Type mType;

// Private
	protected double mNumberValue;
	protected string mStringValue;
	protected Json.ValueType mValueType;
}

