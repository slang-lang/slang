
// Library imports
import System.Collections.Iterator;
import System.Collections.List;

// Project imports
import Array;
import Value;


public namespace Json { }

public object JsonObject extends JsonValue implements IIterable {
	public void Constructor() {
		base.Constructor();

		mMembers = new List<JsonValue>();
		mType = JsonType.Object;
	}

	public void Constructor(string key, JsonArray value) {
		Constructor();

		mKey = key;
		mMembers.push_back( cast<JsonValue>( value ) );
	}

	public void Constructor(string key, JsonValue value) {
		Constructor();

		mKey = key;
		mMembers.push_back(value);
	}

	public void Constructor(string key, JsonObject value) {
		Constructor();

		mKey = key;
		mMembers.push_back( cast<JsonValue>( value ) );
	}

	public void addMember(JsonObject value) modify {
		mMembers.push_back( cast<JsonValue>( value ) );
	}

	public void addMember(string key, JsonValue value) modify {
		mMembers.push_back( cast<JsonValue>( new JsonObject(key, value) ) );
	}

	public string getKey() const {
		return mKey;
	}

	public Iterator getIterator() const {
		return new Iterator( cast<ICollection>( mMembers ) );
	}

	public bool isMember(string key) const {
		foreach ( JsonObject value : mMembers ) {
			if ( value.mKey == key ) {
				return true;
			}
		}

		return false;
	}

	public int size() const {
		return mMembers.size();
	}

	public string toString() const {
		string members;
		foreach ( JsonValue value : mMembers ) {
			members += (members ? ", " : "") + value.toString();
		}

		if ( mKey ) {
		    return "\"" + mKey + "\": " + (members ?: "null");
		}

		return "{ " + members + " }";
	}

	public JsonObject operator[](string key) const throws {
		foreach ( JsonObject value : mMembers ) {
			if ( value.mKey == key ) {
				return value;
			}
		}

		throw "invalid key!";
	}

	private string mKey;
	private List<JsonValue> mMembers;
}

