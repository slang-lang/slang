
// Library imports
import System.Collections.IIterable;
import System.Collections.Map;

// Project imports
import Array;
import Value;


public namespace Yaml { }

public object YamlObject extends YamlValue implements IIterable {
	public void Constructor() {
		base.Constructor();

		mMembers   = new Map<string, YamlValue>();
		mType      = YamlType.Object;
		mValueType = YamlValueType.Object;
	}

	public void Constructor( string key, YamlArray value ) {
		Constructor();

		mMembers.insert( key, cast<YamlValue>( value ) );
	}

	public void Constructor( string key, YamlValue value ) {
		Constructor();

		mMembers.insert( key, value );
	}

	public void Constructor( string key, YamlObject value ) {
		Constructor();

		mMembers.insert( key, cast<YamlValue>( value ) );
	}

	public void addMember( string key, bool value ) modify {
		mMembers.insert( key, new YamlValue( value ) );
	}

	public void addMember( string key, double value ) modify {
		mMembers.insert( key, new YamlValue( value ) );
	}

	public void addMember( string key, float value ) modify {
		mMembers.insert( key, new YamlValue( value ) );
	}

	public void addMember( string key, int value ) modify {
		mMembers.insert( key, new YamlValue( value ) );
	}

	public void addMember( string key, string value ) modify {
		mMembers.insert( key, new YamlValue( value ) );
	}

	public void addMember( string key, YamlArray value ) modify {
		mMembers.insert( key, cast<YamlValue>( value ) );
	}

	public void addMember( string key, YamlObject value ) modify {
		mMembers.insert( key, cast<YamlValue>( value ) );
	}

	public void addMember( string key, YamlValue value ) modify {
		mMembers.insert( key, value );
	}

	public Iterator getIterator() const {
		return mMembers.getIterator();
	}

	public bool isMember( string key ) const {
		return mMembers.contains( key );
	}

	public void set( string key, YamlValue value ) modify {
		foreach ( Pair<string, YamlValue> p : mMembers ) {
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

		foreach ( Pair<string, YamlValue> p : mMembers ) {
			members += ( members ? ", " : "" ) + "\"" + p.first + "\": " + p.second.toString();
		}

		return "{ " + members + " }";
	}

	public YamlValue operator[]( int index ) const throws {
		int count;
		foreach ( Pair<string, YamlValue> p : mMembers ) {
			if ( count == index ) {
				return p.second;
			}

			count++;
		}

		throw "invalid index!";
	}

	public YamlValue operator[]( string key ) const throws {
		foreach ( Pair<string, YamlValue> p : mMembers ) {
			if ( p.first == key ) {
				return p.second;
			}
		}

		throw "invalid key( '" + key + "' )!";
	}

	public string =operator( string ) const {
		return toString();
	}

	private Map<string, YamlValue> mMembers;
}

