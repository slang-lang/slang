
// Library imports

// Project imports


private object SemVer const {
	/*
	 * Static factory, parses a string and returns a valid SemVer object
	 * throws string exception
	 */
	public static SemVer FromString(string version) throws {
		int dot1 = strfind(version, ".");
		if ( !dot1 ) {
			throw "invalid semantic version number '" + version + "'";
		}

		int dot2 = strfind(version, ".", dot1 + 1);
		if ( !dot2 ) {
			throw "invalid semantic version number '" + version + "'";
		}

		if ( dot1 == -1 || dot2 == -1 || strlen(version) < 5 ) {
			throw "invalid semantic version number '" + version + "'";
		}

		var dash = strfind(version, "-", dot2 + 1);
		var label = (dash != -1) ? substr(version, dash + 1) : "";

		return new SemVer( cast<int>( substr(version, 0, dot1) ),
				   cast<int>( substr(version, dot1 + 1, dot2) ),
				   cast<int>( substr(version, dot2 + 1) ),
				   label );
	}


	/*
	 * Public members which indicate the major, minor, bugfix version and an optional label
	 */
	public int Bugfix const;
	public string Label const;
	public int Major const;
	public int Minor const;

	/*
	 * Default constructor
	 */
	public void Constructor(int _major, int _minor, int _bugfix , string _label = "") {
		Major = _major;
		Minor = _minor;
		Bugfix = _bugfix;
		Label = _label;
	}

	/*
	 * returns the next bugfix version based on the current version
	 */
	public SemVer nextBugfix() const {
		return new SemVer(Major, Minor, Bugfix + 1);
	}

	/*
	 * returns the next major version based on the current version
	 */
	public SemVer nextMajor() const {
		return new SemVer(Major + 1, 0, 0);
	}

	/*
	 * returns the next minor version based on the current version
	 */
	public SemVer nextMinor() const {
		return new SemVer(Major, Minor + 1, 0);
	}

	/*
	 * less compare operator
	 */
	public bool operator<(SemVer other const) const {
		if ( Major == other.Major ) {
			if ( Minor == other.Minor ) {
				if ( Bugfix == other.Bugfix ) {
					return Label < other.Label;
				}

				return Bugfix < other.Bugfix;
			}

			return Minor < other.Minor;
		}

		return Major < other.Major;
	}

	/*
	 * string cast operator
	 */
	public string =operator(string) const {
		return cast<string>( Major )
			+ "." + cast<string>( Minor )
			+ "." + cast<string>( Bugfix )
			+ Label ? "-" + Label : "";
	}
}

