
// Library imports

// Project imports
import Array;
import Exceptions;
import Object;


public namespace Json { }

public object JsonWriter {
// Public
	public void Constructor() {
		mIndentation = 0;
		mNumIndents = 0;
		mWhiteSpaceEnd = " ";
		mWhiteSpaceStart = " ";
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

			result += indent( mIndentation ) + "\"" + p.first + "\": " + toString( p.second );
		}
		mIndentation--;

		return "{" + mWhiteSpaceStart + result + mWhiteSpaceEnd + indent( mIndentation ) + "}";
	}

	public string toString( JsonValue root const ) modify throws {
		if ( !root ) {
			throw new JsonException( "invalid JsonValue provided!" );
		}

		if ( root is JsonArray ) {
			return toString( JsonArray root );
		}
		else if ( root is JsonObject ) {
			return toString( JsonObject root );
		}

		return root.toString();
	}

// Protected
	protected string indent( int level ) const {
		return strlpad( "", level * mNumIndents, " " );
	}

	protected int mIndentation;
	protected int mNumIndents;
	protected string mWhiteSpaceEnd;
	protected string mWhiteSpaceStart;
}

public object JsonStyledWriter extends JsonWriter {
// Public
	public void Constructor() {
		mIndentation = 0;
		mNumIndents = 3;
		mWhiteSpaceEnd = LINEBREAK;
		mWhiteSpaceStart = LINEBREAK;
	}
}

