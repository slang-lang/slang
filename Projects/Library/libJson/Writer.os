
// Library imports

// Project imports
import Array;
import Exceptions;
import Object;


public namespace Json {
}


public object JsonWriter {
// Public
	public void Constructor() {
		mIndentation = 0;
		mWhiteSpaceEnd = "";
		mWhiteSpaceIndent = "";
		mWhiteSpaceStart = "";
	}

	public string toString( JsonArray root const ) modify throws {
		string result;

		if ( root.size() ) {
			mIndentation++;
			foreach ( JsonValue value : root ) {
				if ( result ) {
					result += "," + mWhiteSpaceEnd;
				}

				result += indent( mIndentation ) + toString( value );
			}
			mIndentation--;
		}

		return "[" + mWhiteSpaceStart + result + mWhiteSpaceEnd + indent( mIndentation ) + "]";
	}

	public string toString( JsonObject root const ) modify throws {
		string result;

		mIndentation++;
		foreach ( Pair<string, JsonValue> p : root ) {
			if ( result ) {
				result += "," + mWhiteSpaceEnd;
			}

			result += indent( mIndentation) + "\"" + p.first + "\": " + toString( p.second );
		}
		mIndentation--;

		return "{" + mWhiteSpaceStart + result + mWhiteSpaceEnd + indent( mIndentation) + "}";
	}

	public string toString( JsonValue root const ) modify throws {
		if ( !root ) {
			throw new JsonException( "invalid JsonValue provided!" );
		}

		string result;

		// handle complex types
		if ( root is JsonArray ) {
			result += toString( JsonArray root );
		}
		else if ( root is JsonObject ) {
			result += toString( JsonObject root );
		}
		else {
			result += root.toString();
		}

		// handle value types
		return result;
	}

// Protected
	protected string indent( int level ) const {
		//return "";
		return strlpad( "", level * 3, " " );
	}

	protected int mIndentation;
	protected string mWhiteSpaceEnd;
	protected string mWhiteSpaceIndent;
	protected string mWhiteSpaceStart;
}

public object JsonStyledWriter extends JsonWriter {
// Public
	public void Constructor() {
		mIndentation = 0;
		mWhiteSpaceEnd = LINEBREAK_UNIX;
		mWhiteSpaceIndent = "     ";
		mWhiteSpaceStart = LINEBREAK_UNIX;
	}

// Protected
	protected string indent( int level ) const {
		return strlpad( "", level * 3, " " );
	}
}

