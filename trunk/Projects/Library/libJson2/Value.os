
import System.Collections.Vector;
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

public object Value {
// Public
	public void Constructor() {
		mNumberValue = 0;
		mStringValue = "null";
		mValueType = ValueType.Nil;
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
		if ( mValueType == ValueType.String ) {
			return bool mStringValue;
		}

		return bool mNumberValue;
	}

	public double asDouble() const throws {
		if ( mValueType == ValueType.String ) {
			throw new InvalidTypeException();
		}

		return double mNumberValue;
	}

	public float asFloat() const throws {
		if ( mValueType == ValueType.String ) {
			throw new InvalidTypeException();
		}

		return float mNumberValue;
	}

	public int asInt() const throws {
		if ( mValueType == ValueType.String ) {
			throw new InvalidTypeException();
		}

		return int mNumberValue;
	}

	public string asString() const {
		if ( mValueType == ValueType.String ) {
			return mStringValue;
		}

		return string mNumberValue;
	}

	public string getKey() const {
		return mKey;
	}

	public Type getType() const {
		return mType;
	}

	public ValueType getValueType() const {
		return mValueType;
	}

	public void setValue(bool value) modify {
		mNumberValue = value;
		mType = Type.Value;
		mValueType = ValueType.Bool;
	}

	public void setValue(double value) modify {
		mNumberValue = value;
		mType = Type.Value;
		mValueType = ValueType.Double;
	}

	public void setValue(float value) modify {
		mNumberValue = value;
		mType = Type.Value;
		mValueType = ValueType.Float;
	}

	public void setValue(int value) modify {
		mNumberValue = value;
		mType = Type.Value;
		mValueType = ValueType.Int;
	}

	public void setValue(string value) modify {
		mStringValue = value;
		mType = Type.Value;
		mValueType = ValueType.String;
	}

	public string toString() const {
		if ( mValueType == ValueType.String ) {
			return "\"" + mStringValue + "\"";
		}

		return string mNumberValue;
	}

	public Value operator=(Value value) modify {
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
	protected Type mType;

// Private
	protected Vector mMembers;
	protected double mNumberValue;
	protected string mStringValue;
	protected ValueType mValueType;
}

}

