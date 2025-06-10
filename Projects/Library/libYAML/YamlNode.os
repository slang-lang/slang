
// library imports
import System.Collections.Map;
import System.Collections.Vector;

// project imports


public namespace Yaml { }


public enum YamlNodeType {
	Map,
	Null,
	Sequence,
	Value;
}


public object YamlNode {
	protected YamlNodeType type;
	protected YamlNode value;

	public void Constructor() {
		type = YamlNodeType.Null;
	}

	public YamlNode operator[]( int key ) {
		if ( type == YamlNodeType.Map ) {
			return ( YamlMap value ).nodes.get( cast<string>( key ) );
		}

		return YamlNode null;
	}
	public YamlNode operator[]( string key ) {
		if ( type == YamlNodeType.Map ) {
			return ( YamlMap value ).nodes.get( cast<string>( key ) );
		}

		return YamlNode null;
	}

	public void push_back( string value ) {
		if ( type == YamlNodeType.Map ) {
			
		}
	}

	public string =operator( string ) const {
		return cast<string>( type );
	}
}


private object YamlMap extends YamlNode {
	public Map<string, YamlNode> nodes;
}

private object YamlVector extends YamlNode {
	public Vector<YamlNode> nodes;
}

