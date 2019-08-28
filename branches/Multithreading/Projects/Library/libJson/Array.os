
// Library imports
import System.Collections.Iterator;
import System.Collections.Vector;

// Project imports
import Value;


public namespace Json { }

public object JsonArray extends JsonValue implements IIterateable {
	public void Constructor(string key) {
		base.Constructor();

		mKey = key;
		mMembers = new Vector<JsonValue>();
		mType = JsonType.Array;
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

	public string getKey() const {
		return mKey;
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

	private string mKey;
	private Vector<JsonValue> mMembers;
}

