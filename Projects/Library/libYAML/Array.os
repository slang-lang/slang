
// Library imports
import System.Collections.IIterable;
import System.Collections.Vector;

// Project imports
import Value;


public namespace Yaml { }

public object YamlArray extends YamlValue implements IIterable {
	public void Constructor() {
		base.Constructor();

		mMembers   = new Vector<YamlValue>();
		mType      = YamlType.Array;
		mValueType = YamlValueType.Array;
	}

	public void addMember( YamlArray value ) modify {
		mMembers.insert( mMembers.size(), cast<YamlValue>( value ) );
	}

	public void addMember( YamlValue value ) modify {
		mMembers.insert( mMembers.size(), value );
	}

	public void addMember( YamlObject value ) modify {
		mMembers.insert( mMembers.size(), cast<YamlValue>( value ) );
	}

	public Iterator<YamlValue> getIterator() const {
		return mMembers.getIterator();
	}

	public int size() const {
		return mMembers.size();
	}

	public string toString() const {
		string members;

		foreach ( YamlValue value : mMembers ) {
			members += ( members ? ", " : "" ) + value.toString();
		}

		return "[ " + members + " ]";
	}

	public YamlValue operator[]( int index ) const throws {
		return mMembers.at( index );
	}

	public string =operator( string ) const {
		return toString();
	}

	private Vector<YamlValue> mMembers;
}

