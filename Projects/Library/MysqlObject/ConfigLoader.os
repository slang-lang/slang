
// Library imports
import libJson.Object;
import libJson.Reader;
import libJson.Writer;
import System.IO.File;

// Project imports


public object Config {
	public string Database;
	public string Host = "localhost";
	public string Password;
	public int Port = 3306;
	public string User;

	public string TablePrefix = "T_";
	public string TablePostfix = "Record";
	public string ViewPrefix = "V_";
	public string ViewPostfix = "Record";
}


public object ConfigLoader {
	public void Constructor(string filename) {
		mConfig = new Config();
		mFilename = filename;
	}

	public bool load() modify {
		if ( !System.IO.File.FileExists( mFilename ) ) {
			return false;
		}

		var file = new System.IO.File( mFilename, System.IO.FileAccessMode.ReadOnly );
		if ( !file.isOpen() ) {
			return false;
		}

		string text;
		while ( !file.isEOF() ) {
			text += file.readChar();
		}

		var reader = new JsonReader();
		var config = JsonObject reader.parse( text );
		//print( "Reader: " + config.toString() );

		// Database config
		// {
		if ( config.isMember( "Database" ) ) mConfig.Database = config[ "Database" ].asString();
		if ( config.isMember( "Host" ) ) mConfig.Host = config[ "Host" ].asString();
		if ( config.isMember( "Password" ) ) mConfig.Password = config[ "Password" ].asString();
		if ( config.isMember( "Port" ) ) mConfig.Port = config[ "Port" ].asInt();
		if ( config.isMember( "User" ) ) mConfig.User = config[ "User" ].asString();
		// }

		// Item config
		// {
		if ( config.isMember( "TablePrefix" ) ) mConfig.TablePrefix = config[ "TablePrefix" ].asString();
		if ( config.isMember( "TablePostfix" ) ) mConfig.TablePostfix = config[ "TablePostfix" ].asString();
		if ( config.isMember( "ViewPrefix" ) ) mConfig.ViewPrefix = config[ "ViewPrefix" ].asString();
		if ( config.isMember( "ViewPostfix" ) ) mConfig.ViewPostfix = config[ "ViewPostfix" ].asString();
		// }

		return true;
	}

	public void store() {
		var config = new JsonObject();

		// Database config
		// {
		config.addMember( "Database", new JsonValue( mConfig.Database ) );
		config.addMember( "Host", new JsonValue( mConfig.Host ) );
		config.addMember( "Password", new JsonValue( mConfig.Password ) );
		config.addMember( "Port", new JsonValue( mConfig.Port ) );
		config.addMember( "User", new JsonValue( mConfig.User ) );
		// }

		// Item config
		// {
		config.addMember( "TablePrefix", new JsonValue( mConfig.TablePrefix ) );
		config.addMember( "TablePostfix", new JsonValue( mConfig.TablePostfix ) );
		config.addMember( "ViewPrefix", new JsonValue( mConfig.ViewPrefix ) );
		config.addMember( "ViewPostfix", new JsonValue( mConfig.ViewPostfix ) );
		// }

		//print( "Writer: " + config.toString() );

		var file = new System.IO.File( mFilename, System.IO.FileAccessMode.WriteOnly );
		//file.write( new JsonStyledWriter().toString( config ) );		// writers currently don't work ;-(
		file.write( config.toString() );
		file.close();
	}

	private Config mConfig;
	private string mFilename;
}

