
// Library imports
import System.Collections.Iterator;
import System.Collections.List;

// Project imports
import Value;


public namespace Json {
}

public object JsonObject extends JsonValue implements IIterateable {
	public void Constructor() {
		base.Constructor();

		mMembers = new List<JsonValue>();
		mType = Json.Type.Object;
	}

	public void Constructor(string key, JsonValue value) {
		Constructor();

		mKey = key;
		mMembers.push_back(value);
	}

	public void addMember(JsonObject value) modify {
		mMembers.push_back(JsonValue value);
	}

	public void addMember(string key, JsonValue value) modify {
		mMembers.push_back(JsonValue new JsonObject(key, value));
	}

	public Iterator getIterator() const {
		return new Iterator(ICollection mMembers);
	}

	public string toString() const {
		string members;
		foreach ( JsonValue value : mMembers ) {
			members += (members ? "," : "") + value.toString();
		}

		return "{\"" + mKey + "\":" + (members ?: "null") + "}";
	}

	private List<JsonValue> mMembers;
}

