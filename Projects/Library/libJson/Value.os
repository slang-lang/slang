
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
		mObjectValue = JsonValue null;
		mType = JsonType.Value;
		mValue = "null";
		mValueType = JsonValueType.Null;
	}

	public void Constructor( bool value ) {
		setValue( value );
	}

	public void Constructor( double value ) {
		setValue( value );
	}

	public void Constructor( float value ) {
		setValue( value );
	}

	public void Constructor( int value ) {
		setValue( value );
	}

	public void Constructor( string value ) {
		setValue( value );
	}

	public void Constructor( JsonArray array ) {
		setValue( cast<JsonValue>( array ) );
	}

	public void Constructor( JsonObject obj ) {
		setValue( cast<JsonValue>( obj ) );
	}

	public bool asBool() const {
		if ( mValueType == JsonValueType.Object ) {
			return bool mObjectValue;
		}

		return bool mValue;
	}

	public double asDouble() const throws {
		if ( mValueType == JsonValueType.Object
		  || mValueType == JsonValueType.String ) {
			throw new InvalidTypeException();
		}

		return cast<double>( mValue );
	}

	public float asFloat() const throws {
		if ( mValueType == JsonValueType.Object
		  || mValueType == JsonValueType.String ) {
			throw new InvalidTypeException();
		}

		return cast<float>( mValue );
	}

	public int asInt() const throws {
		if ( mValueType == JsonValueType.Object
		  || mValueType == JsonValueType.String ) {
			throw new InvalidTypeException();
		}

		return cast<int>( mValue );
	}

	public string asString() const {
		if ( mValueType == JsonValueType.Object ) {
			return mObjectValue.asString();
		}

		return cast<string>( mValue );
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

	public void setValue( bool value ) modify {
		mObjectValue = JsonValue null;
		mValue = cast<string>( value );
		mType = JsonType.Value;
		mValueType = JsonValueType.Bool;
	}

	public void setValue( double value ) modify {
		mObjectValue = JsonValue null;
		mValue = cast<string>( value );
		mType = JsonType.Value;
		mValueType = JsonValueType.Number;
	}

	public void setValue( float value ) modify {
		mObjectValue = JsonValue null;
		mValue = cast<string>( value );
		mType = JsonType.Value;
		mValueType = JsonValueType.Number;
	}

	public void setValue( int value ) modify {
		mObjectValue = JsonValue null;
		mValue = cast<string>( value );
		mType = JsonType.Value;
		mValueType = JsonValueType.Number;
	}

	public void setValue( string value ) modify {
		mObjectValue = JsonValue null;
		mValue = value;
		mType = JsonType.Value;
		mValueType = JsonValueType.String;
	}

	public void setValue( JsonValue value ) modify {
		mObjectValue = value;
		mValue = "";
		mType = value.getType();
		mValueType = value.getValueType();
	}

	public int size() const {
		return 0;
	}

	public string toString() const throws {
		switch ( mType ) {
			case JsonType.Array: {
				return (JsonArray mObjectValue).toString();
			}
			case JsonType.Object: {
				return (JsonObject mObjectValue).toString();
			}
			case JsonType.Value: {
				switch ( mValueType ) {
					case JsonValueType.String: {
						return "\"" + mValue + "\"";
					}
					default: {
						return cast<string>( mValue );
					}
				}
				break;
			}
		}

		throw "not implemented";
	}

	public bool operator=( bool value ) modify {
		setValue( value );

		return value;
	}

	public double operator=( double value ) modify {
		setValue( value );

		return value;
	}

	public float operator=( float value ) modify {
		setValue( value );

		return value;
	}

	public int operator=( int value ) modify {
		setValue( value );

		return value;
	}

	public string operator=( string value ) modify {
		setValue( value );

		return value;
	}

	public JsonArray operator=( JsonArray value ) modify {
		setValue( cast<JsonValue>( value ) );

		return JsonArray mObjectValue;
	}

	public JsonObject operator=( JsonObject value ) modify {
		setValue( cast<JsonValue>( value ) );

		return JsonObject mObjectValue;
	}

	public JsonValue operator=( JsonValue value ) modify {
		setValue( value );

		return this;
	}

	public string =operator( string ) const {
		return toString();
	}

// Protected
	protected JsonValue mObjectValue;
	protected string mValue;
	protected JsonType mType;
	protected JsonValueType mValueType;
}

