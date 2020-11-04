
// Library imports
import System.Collections.IIterable;
import System.Collections.Map;

// Project imports
import Array;
import Value;


public namespace Json { }

public object JsonObject extends JsonValue implements IIterable {
	public void Constructor() {
		base.Constructor();

		mMembers = new Map<string, JsonValue>();
		mType = JsonType.Object;
	}

	public void Constructor( string key, JsonArray value ) {
		Constructor();

		mMembers.insert( key, cast<JsonValue>( value ) );
	}

	public void Constructor( string key, JsonValue value ) {
		Constructor();

		mMembers.insert( key, value );
	}

	public void Constructor( string key, JsonObject value ) {
		Constructor();

		mMembers.insert( key, cast<JsonValue>( value ) );
	}

	public void addMember( string key, bool value ) modify {
		mMembers.insert( key, new JsonValue( value ) );
	}

	public void addMember( string key, double value ) modify {
		mMembers.insert( key, new JsonValue( value ) );
	}

	public void addMember( string key, float value ) modify {
		mMembers.insert( key, new JsonValue( value ) );
	}

	public void addMember( string key, int value ) modify {
		mMembers.insert( key, new JsonValue( value ) );
	}

	public void addMember( string key, string value ) modify {
		mMembers.insert( key, new JsonValue( value ) );
	}

	public void addMember( string key, JsonArray value ) modify {
		mMembers.insert( key, cast<JsonValue>( value ) );
	}

	public void addMember( string key, JsonObject value ) modify {
		mMembers.insert( key, cast<JsonValue>( value ) );
	}

	public void addMember( string key, JsonValue value ) modify {
		mMembers.insert( key, value );
	}

	public Iterator getIterator() const {
		return mMembers.getIterator();
	}

	public bool isMember( string key ) const {
		return mMembers.contains( key );
	}

	public void set( string key, JsonValue value ) modify {
		foreach ( Pair<string, JsonValue> p : mMembers ) {
			if ( p.first == key ) {
				p.second = value;
				return;
			}
		}

		addMember( key, value );
	}

	public int size() const {
		return mMembers.size();
	}

	public string toString() const {
		string members;

		foreach ( Pair<string, JsonValue> p : mMembers ) {
			members += ( members ? ", " : "" ) + "\"" + p.first + "\": " + p.second.toString();
		}

		return "{ " + members + " }";
	}

	public JsonValue operator[]( int index ) const throws {
		int count;
		foreach ( Pair<string, JsonValue> p : mMembers ) {
			if ( count == index ) {
				return p.second;
			}

			count++;
		}

		throw "invalid index!";
	}

	public JsonValue operator[]( string key ) const throws {
		foreach ( Pair<string, JsonValue> p : mMembers ) {
			if ( p.first == key ) {
				return p.second;
			}
		}

		throw "invalid key('" + key + "')!";
	}

	private Map<string, JsonValue> mMembers;
}

