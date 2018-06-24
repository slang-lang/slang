
// Library imports
import System.Collections.Iterator;
import System.Collections.Vector;

// Project imports
import Value;


public namespace Json {
}

public object JsonArray extends JsonValue implements IIterateable {
	public void Constructor() {
		base.Constructor();

		mMembers = new Vector<JsonValue>();
		mType = Json.Type.Array;
	}

	public void Constructor(string key) {
		Constructor();

		mKey = key;
	}

	public void addMember(JsonValue value) modify {
		mMembers.insert(mMembers.size(), value);
	}

	public void addMember(JsonObject value) modify {
		mMembers.insert(mMembers.size(), JsonValue value);
	}

	public Iterator getIterator() const {
		return new Iterator(ICollection mMembers);
	}

	public int size() const {
		return mMembers.size();
	}

	public string toString() const {
		string members;

		foreach ( JsonValue value : mMembers ) {
			members += (members ? "," : "") + value.toString();
		}

		return "{ \"" + mKey + "\": [" + (members ?: "") + "] }";
	}

	private Vector<JsonValue> mMembers;
}

