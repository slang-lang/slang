
// Library imports
import System.Collections.IIterable;
import System.Collections.Vector;

// Project imports
import Value;


public namespace Json { }

public object JsonArray extends JsonValue implements IIterable {
	public void Constructor() {
		base.Constructor();

		mMembers = new Vector<JsonValue>();
		mType = JsonType.Array;
	}

	public void addMember( JsonArray value ) modify {
		mMembers.insert( mMembers.size(), cast<JsonValue>( value ) );
	}

	public void addMember( JsonValue value ) modify {
		mMembers.insert( mMembers.size(), value );
	}

	public void addMember( JsonObject value ) modify {
		mMembers.insert( mMembers.size(), cast<JsonValue>( value ) );
	}

	public Iterator<JsonValue> getIterator() const {
		return new Iterator<JsonValue>( ICollection mMembers );
	}

	public int size() const {
		return mMembers.size();
	}

	public string toString() const {
		string members;

		foreach ( JsonValue value : mMembers ) {
			members += ( members ? ", " : "" ) + value.toString();
		}

		return "[ " + members + " ]";
	}

	public JsonValue operator[]( int index ) const throws {
		return mMembers.at( index );
	}

	private Vector<JsonValue> mMembers;
}

