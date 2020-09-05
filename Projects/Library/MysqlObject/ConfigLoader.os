
// Library imports
import libJson.Object;
import libJson.Reader;
import libJson.Writer;
import System.IO.File;

// Project imports


public object Config {
	public string Database;
	public string Host = "localhost";
	public string Output;
	public string Password;
	public int Port = 3306;
	public string User;

	public string toString() const {
		return "Database: '" + Database + "', Host: '" + Host + "', Output: '" + Output + "', User: '" + User + "'";
	}
}


public object ConfigLoader {
	public void Constructor( string filename ) {
		mConfig = new Config();
		mFilename = filename;
	}

	public bool load() modify {
		if ( !System.IO.File.FileExists( mFilename ) ) {
			return false;
		}

		var file = new System.IO.File( mFilename, System.IO.File.AccessMode.ReadOnly );
		if ( !file.isOpen() ) {
			return false;
		}

		string text;
		while ( !file.isEOF() ) {
			text += file.readChar();
		}

		var reader = new JsonReader();
		var config = JsonObject reader.parse( text );

		print( config.toString() );

		// Database config
		// {
		mConfig.Database	= config.isMember( "Database" )	? config[ "Database" ].asString()	: Database;
		mConfig.Host		= config.isMember( "Host" )		? config[ "Host" ].asString()		: Host;
		mConfig.Output		= config.isMember( "Output" )	? config[ "Output" ].asString()		: Output;
		mConfig.Password	= config.isMember( "Password" )	? config[ "Password" ].asString()	: Password;
		mConfig.Port		= config.isMember( "Port" )		? config[ "Port" ].asInt()			: Port;
		mConfig.User		= config.isMember( "User" )		? config[ "User" ].asString()		: User;
		// }

		print( mConfig.toString() );

		return true;
	}

	public void store() {
		var config = new JsonObject();

		// Database config
		// {
		config.addMember( "Database",	new JsonValue( mConfig.Database ) );
		config.addMember( "Host",	new JsonValue( mConfig.Host ) );
		config.addMember( "Output",	new JsonValue( mConfig.Output ) );
		config.addMember( "Password",	new JsonValue( mConfig.Password ) );
		config.addMember( "Port",	new JsonValue( mConfig.Port ) );
		config.addMember( "User",	new JsonValue( mConfig.User ) );
		// }

		print( "Writer: " + config.toString() );

		var file = new System.IO.File( mFilename, System.IO.File.AccessMode.WriteOnly );
		file.write( config.toString() );
		file.close();
	}

	private Config mConfig;
	private string mFilename;
}

