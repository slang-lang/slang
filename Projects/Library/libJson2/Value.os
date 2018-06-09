
import Exceptions;

public namespace Json {

public object Value {
// Public
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
		String
		;
	}

	public void Constructor() {
	}

	public void Constructor(string key, bool value) {
		mKey = key;

		setValue(value);
	}

	public void Constructor(string key, double value) {
		mKey = key;

		setValue(value);
	}

	public void Constructor(string key, string value) {
		mKey = key;

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

	public bool operator=(bool value) modify {
		setValue(value);

		return value;
	}

	public double operator=(double value) modify {
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
	private double mNumberValue;
	private string mStringValue;
	private ValueType mValueType;
}

}

