
// Library imports
import System.Collections.Map;

// Project imports


public object DatatypeMapper {
	public Map</*source*/ string, /*target*/ string> DataTypes;

	public void Constructor() {
		DataTypes = new Map<string, string>();

		InitDataTypes();
	}

	public void addType(string left, string right) modify {
		DataTypes.insert(left, right);
	}

	public string lookupType(string type) const throws {
		foreach ( Pair<string, string> p : DataTypes ) {
			if ( p.first == type ) {
				return p.second;
			}
		}

		throw new Exception("Type '" + type + "' not found!");
	}

	private void InitDataTypes() modify {
		DataTypes.insert("datetime",	"string");
		DataTypes.insert("float",	"float");
		DataTypes.insert("int",		"int");
		DataTypes.insert("mediumtext",	"string");
		DataTypes.insert("text",	"string");
		DataTypes.insert("tinyint",	"bool");
		DataTypes.insert("timestamp",	"int");
		DataTypes.insert("varchar",	"string");
	}
}

