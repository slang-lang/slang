
// Library imports
import System.Collections.Set;

// Project imports
import libSemVer.SemVer;


private object Module {
	public string architecture;
	public string description;
	public Set<string> keywords;
	public string name;
	public SemVer version;

	public void Constructor( string _name, SemVer _version, string _architecture = "", string _description = "", Set<string> keywords_ = null ) {
		architecture = _architecture;
		description = _description;
		name = _name;
		version = _version;
	}

	public void Constructor( string _name, string _version, string _architecture = "", string _description = "", Set<string> keywords_ = null ) {
		Constructor( _name, SemVer.FromString( _version ), _architecture, _description, keywords );
	}

	public bool isValid() {
		return name && version;
	}

	public string toString() {
		return name + ":" + cast<string>( version );
	}

	public bool operator==( Module other const ) {
		return name == other.name;
	}

	public bool operator<( Module other const ) {
		if ( name == other.name ) {
			return version < other.version;
		}

		return name < other.name;
	}
}

