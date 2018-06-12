
import Array;
import Exceptions;
import Object;


public namespace Json {
}


public object JsonWriter {
	public string toString(JsonValue root const ref) const throws {
		if ( !root ) {
			throw new Exception("invalid Json Value provided!");
		}

		// handle complex types
		if ( root is JsonArray ) {
			return toString(JsonArray root);
		}
		else if ( root is JsonObject ) {
			return toString(JsonObject root);
		}

		// handle value types
		if ( root.isString() ) {
			return "\"" + root.toString() + "\"";
		}

		return root.toString();
	}

	protected string toString(JsonArray root const ref) const {
		string result;

		foreach ( JsonValue value : root ) {
			if ( result ) {
				result += ",";
			}
			result += toString(value);
		}

		return "[" + result + "]";
	}

	protected string toString(JsonObject root const ref) const {
		string result;

		foreach ( JsonValue value : root ) {
			if ( result ) {
				result += ",";
			}
			result += toString(value);
		}

		return "{" + result + "}";
	}
}

public object JsonStyledWriter extends JsonWriter {
    public void Constructor() {
        mWhiteSpaceEnd = ascii(10);
        mWhiteSpaceStart = ascii(10);
    }

    protected string indent(int num) const {
        string result;
        for ( int i = 0; i < num; i++ ) {
            result += mWhiteSpaceIndent;
        }
        return result;
    }

    protected string mWhiteSpaceEnd;
    protected string mWhiteSpaceIndent = "     ";
    protected string mWhiteSpaceStart;
}

