
// Library imports

// Project imports
import Array;
import Exceptions;
import Object;


public namespace Yaml { }

public enum YamlType {
	Array,
	Object,
	Value
}

public enum YamlValueType {
	Array,
	Bool,
	Null,
	Number,
	Object,
	String
}


public object YamlValue {
// Public
	public void Constructor() {
		mObjectValue = YamlValue null;
		mType        = YamlType.Value;
		mValue       = "null";
		mValueType   = YamlValueType.Null;
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

	public void Constructor( YamlArray array ) {
		setValue( cast<YamlValue>( array ) );
	}

	public void Constructor( YamlObject obj ) {
		setValue( cast<YamlValue>( obj ) );
	}

	public YamlArray asArray() const throws {
		if ( mValueType != YamlValueType.Array ) {
			throw new InvalidTypeException( "array" );
		}

		return YamlArray mObjectValue;
	}

	public bool asBool() const {
		if ( mValueType == YamlValueType.Object ) {
			return bool mObjectValue;
		}

		return bool mValue;
	}

	public double asDouble() const throws {
		if ( mValueType != YamlValueType.Array && mValueType != YamlValueType.Object ) {
			throw new InvalidTypeException( "double" );
		}

		return cast<double>( mValue );
	}

	public float asFloat() const throws {
		if ( mValueType != YamlValueType.Array && mValueType != YamlValueType.Object ) {
			throw new InvalidTypeException( "float" );
		}

		return cast<float>( mValue );
	}

	public int asInt() const throws {
		if ( mValueType != YamlValueType.Array && mValueType != YamlValueType.Object ) {
			throw new InvalidTypeException( "int" );
		}

		return cast<int>( mValue );
	}

	public YamlObject asObject() const throws {
		if ( mValueType != YamlValueType.Array && mValueType != YamlValueType.Object ) {
			throw new InvalidTypeException( "object" );
		}

		return YamlObject mObjectValue;
	}

	public string asString() const {
		if ( mValueType != YamlValueType.Array && mValueType != YamlValueType.Object ) {
			return cast<string>( mValue );
		}

		return mObjectValue.asString();
	}

	public YamlType getType() const {
		return mType;
	}

	public YamlValueType getValueType() const {
		return mValueType;
	}

	public bool isArray() const {
		return mValueType == YamlValueType.Array;
	}

	public bool isBool() const {
		return mValueType == YamlValueType.Bool;
	}

	public bool isNull() const {
		return mValueType == YamlValueType.Null;
	}

	public bool isNumber() const {
		return mValueType == YamlValueType.Number;
	}

	public bool isObject() const {
		return mValueType == YamlValueType.Object;
	}

	public bool isString() const {
		return mValueType == YamlValueType.String;
	}

	public void setValue( bool value ) modify {
		mObjectValue = YamlValue null;
		mValue       = cast<string>( value );
		mType        = YamlType.Value;
		mValueType   = YamlValueType.Bool;
	}

	public void setValue( double value ) modify {
		mObjectValue = YamlValue null;
		mValue       = cast<string>( value );
		mType        = YamlType.Value;
		mValueType   = YamlValueType.Number;
	}

	public void setValue( float value ) modify {
		mObjectValue = YamlValue null;
		mValue       = cast<string>( value );
		mType        = YamlType.Value;
		mValueType   = YamlValueType.Number;
	}

	public void setValue( int value ) modify {
		mObjectValue = YamlValue null;
		mValue       = cast<string>( value );
		mType        = YamlType.Value;
		mValueType   = YamlValueType.Number;
	}

	public void setValue( string value ) modify {
		mObjectValue = YamlValue null;
		mValue       = value;
		mType        = YamlType.Value;
		mValueType   = YamlValueType.String;
	}

	public void setValue( YamlValue value ) modify {
		mObjectValue = value;
		mValue       = "";
		mType        = value.getType();
		mValueType   = value.getValueType();
	}

	public int size() const {
		return 0;
	}

	public string toString() const throws {
		switch ( mType ) {
			case YamlType.Array: {
				return ( YamlArray mObjectValue ).toString();
			}
			case YamlType.Object: {
				return ( YamlObject mObjectValue ).toString();
			}
			case YamlType.Value: {
				switch ( mValueType ) {
					case YamlValueType.String: {
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

	public YamlArray operator=( YamlArray value ) modify {
		setValue( cast<YamlValue>( value ) );

		return YamlArray mObjectValue;
	}

	public YamlObject operator=( YamlObject value ) modify {
		setValue( cast<YamlValue>( value ) );

		return YamlObject mObjectValue;
	}

	public YamlValue operator=( YamlValue value ) modify {
		setValue( value );

		return this;
	}

	public string =operator( string ) const {
		return toString();
	}

// Protected
	protected YamlValue mObjectValue;
	protected string mValue;
	protected YamlType mType;
	protected YamlValueType mValueType;
}

