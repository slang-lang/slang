
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

	public string toString(JsonArray root const ref) modify throws {
		return toString(JsonValue root);
	}

	public string toString(JsonObject root const ref) modify throws {
		return toString(JsonValue root);
	}

	public string toString(JsonValue root const ref) modify throws {
		if ( !root ) {
			throw new JsonException("invalid Json Value provided!");
		}

		string result;

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
		return result;
	}

	public string toString2(JsonValue root const) modify throws {
		if ( !root ) {
			throw new JsonException("invalid Json Value provided!");
		}

		string result;

		if ( root.size() ) {
			if ( root is JsonArray ) {
				result += "[";
			}
			else if ( root is JsonObject ) {
				result += "{";
			}
			result += mWhiteSpaceStart + indent(mIndentation);
			//result += "\"" + root.getKey() + "\":";

			string inner;
			mIndentation++;
			foreach ( JsonValue value : (JsonObject root) ) {
				if ( inner ) {
					inner += "," + mWhiteSpaceEnd + indent(mIndentation);
				}

				inner += toString2(value);
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

		return result;
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

		if ( result ) {
			result = "[" + mWhiteSpaceStart + indent(mIndentation) + result + mWhiteSpaceEnd + indent(mIndentation) + "]";
		}
		mIndentation--;

		return "{" + mWhiteSpaceStart + indent(mIndentation + 1) + "\"" + root.getKey() + "\": " + (result ?: "[]") + mWhiteSpaceEnd + indent(mIndentation) + "}";
	}

	protected string _toString(JsonObject root const ref) modify {
		string result;

		mIndentation++;
		foreach ( JsonValue value : root ) {
			if ( result ) {
				result += "," + mWhiteSpaceEnd + indent(mIndentation);
			}

			result += toString(value);
		}
		mIndentation--;

		return "{" + mWhiteSpaceStart + indent(mIndentation + 1) + "\"" + root.getKey() + "\": " + (result ?: "null") + mWhiteSpaceEnd + indent(mIndentation) + "}";
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
	protected string indent(int num) const {
		string result;

		for ( int i = 0; i < num; i++ ) {
			result += mWhiteSpaceIndent;
		}

		return result;
	}
}

