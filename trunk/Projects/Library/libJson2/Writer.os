
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

	public string toString(JsonArray root const ref) modify throws {
		return toString(JsonValue root);
	}

	public string toString(JsonObject root const ref) modify throws {
		return toString(JsonValue root);
	}

	public string toString(JsonValue root const ref) modify throws {
		if ( !root ) {
			throw new Exception("invalid Json Value provided!");
		}

		string result = "{" + mWhiteSpaceStart + indent(mIndentation++) + "\"" + root.getKey() + "\": ";

		// handle complex types
		if ( root is JsonArray ) {
			result += _toString(JsonArray root);
		}
		else if ( root is JsonObject ) {
			result += _toString(JsonObject root);
		}
		else {
			result += root.asString();
		}

		// handle value types
		return result + mWhiteSpaceEnd + indent(mIndentation--) + "}";
	}

	public string toString2(JsonValue root const) modify throws {
		if ( !root ) {
			throw new Exception("invalid Json Value provided!");
		}

		string result = "{" + mWhiteSpaceStart + indent(mIndentation++) + "\"" + root.getKey() + "\": ";

		if ( root.size() ) {
			if ( root is JsonArray ) {
				result += "[";
			}
			else {
				result += "{";
			}
			result += mWhiteSpaceStart;

			string inner;
			mIndentation++;
			foreach ( JsonValue value : (JsonObject root) ) {
				if ( inner ) {
					inner += "," + mWhiteSpaceEnd;
				}

				inner += indent(mIndentation) + toString2(value);
			}
			mIndentation--;

			result += inner + mWhiteSpaceEnd + indent(mIndentation);

			if ( root is JsonArray ) {
				result += "]";
			}
			else {
				result += "}";
			}
		}
		else {
			if ( root is JsonArray ) {
				result += "[]";
			}
			else if ( root is JsonObject) {
				result += "null";
			}
			else {
				result += root.asString();
			}
		}

		return result + mWhiteSpaceEnd + indent(mIndentation--) + "}";
	}

// Protected
    protected string indent(int) const {
        return "";
    }

	protected string _toString(JsonArray root const ref) modify {
		string result;

		mIndentation++;
		foreach ( JsonValue value : root ) {
			if ( result ) {
				result += "," + mWhiteSpaceEnd;
			}

			result += indent(mIndentation) + toString(value);
		}
		mIndentation--;

		return result ? ("[" + mWhiteSpaceStart + indent(mIndentation) + result + mWhiteSpaceEnd + indent(mIndentation) + "]") : "[]";
	}

	protected string _toString(JsonObject root const ref) modify {
		string result;

		mIndentation++;
		foreach ( JsonValue value : root ) {
			if ( result ) {
				result += "," + mWhiteSpaceEnd;
			}

			result += indent(mIndentation) + toString(value);
		}
		mIndentation--;

		return result ? ("{" + mWhiteSpaceStart + indent(mIndentation + 1) + result + mWhiteSpaceEnd + indent(mIndentation) + "}") : "null";
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
        mWhiteSpaceEnd = ascii(10);
		mWhiteSpaceIndent = "     ";
        mWhiteSpaceStart = ascii(10);
    }

// Protected
    protected string indent(int num) const {
        string result;

        for ( int i = 0; i < num; i++ ) {
            result += mWhiteSpaceIndent;
        }

        return result;
    }
}

