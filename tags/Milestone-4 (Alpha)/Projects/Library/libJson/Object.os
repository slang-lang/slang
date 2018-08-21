
// Library imports
import System.Collections.Iterator;
import System.Collections.List;

// Project imports
import Array;
import Value;


public namespace Json { }

public object JsonObject extends JsonValue implements IIterateable {
	public void Constructor() {
		base.Constructor();

		mMembers = new List<JsonValue>();
		mType = Json.Type.Object;
	}

	public void Constructor(string key, JsonArray value) {
		Constructor();

		mKey = key;
		mMembers.push_back(JsonValue value);
	}

	public void Constructor(string key, JsonValue value) {
		Constructor();

		mKey = key;
		mMembers.push_back(value);
	}

	public void Constructor(string key, JsonObject value) {
		Constructor();

		mKey = key;
		mMembers.push_back(JsonValue value);
	}

	public void addMember(JsonObject value) modify {
		mMembers.push_back(JsonValue value);
	}

	public void addMember(string key, JsonValue value) modify {
		mMembers.push_back(JsonValue new JsonObject(key, value));
	}

	public string getKey() const {
		return mKey;
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

		return "{ \"" + mKey + "\": " + (members ?: "null") + " }";
	}

	private string mKey;
	private List<JsonValue> mMembers;
}

