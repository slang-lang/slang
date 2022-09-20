
// Library imports
import libJson;
import System.IO.File;

// Project imports
import Scanner;


public object Config {
	public static string Database;
	public static string Host = "127.0.0.1";
	public static string OutputFormat = "os";
	public static string Password;
	public static string Port = "3306";
	public static string TargetDirectory;
	public static string User;

	public static string toString() const {
		return "Database: '" + Config.Database + "', Host: '" + Config.Host + "', OutputFormat: '" + Config.OutputFormat + "', TargetDirectory: '" + Config.TargetDirectory + "', User: '" + Config.User + "'";
	}
}


public object ConfigLoader {
	public void Constructor( string filename ) {
		mFilename = filename;
	}

	public bool load() modify {
		if ( !System.IO.File.Exists( mFilename ) ) {
			return false;
		}

		var reader = new JsonReader();

		var text = new Scanner( mFilename ).getText();
		var config = JsonObject reader.parse( text );

		print( config.toString() );

		// Database config
		// {
		Config.Database			= config.isMember( "Database" )			?	config[ "Database" ].asString()				: Config.Database;
		Config.Host				= config.isMember( "Host" )				?	config[ "Host" ].asString()					: Config.Host;
		Config.OutputFormat		= config.isMember( "OutputFormat" )		?	config[ "OutputFormat" ].asString()			: Config.OutputFormat;
		Config.Password			= config.isMember( "Password" )			?	config[ "Password" ].asString()				: Config.Password;
		Config.Port				= config.isMember( "Port" )				?	config[ "Port" ].asString()					: Config.Port;
		Config.TargetDirectory	= config.isMember( "TargetDirectory" )	?	config[ "TargetDirectory" ].asString()		: Config.TargetDirectory;
		Config.User				= config.isMember( "User" )				?	config[ "User" ].asString()					: Config.User;
		// }

		//print( Config.toString() );

		return true;
	}

	public void store() {
		var config = new JsonObject();

		// Database config
		// {
		config.addMember( "Database",	new JsonValue( Config.Database ) );
		config.addMember( "Host",	new JsonValue( Config.Host ) );
		config.addMember( "OutputFormat",	new JsonValue( Config.OutputFormat ) );
		config.addMember( "Password",	new JsonValue( Config.Password ) );
		config.addMember( "Port",	new JsonValue( Config.Port ) );
		config.addMember( "TargetDirectory",	new JsonValue( Config.TargetDirectory ) );
		config.addMember( "User",	new JsonValue( Config.User ) );
		// }

		var file = new System.IO.File( mFilename, System.IO.File.AccessMode.WriteOnly );
		file.write( config.toString() );
		file.close();
	}

	private string mFilename const;
}

