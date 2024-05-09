
// Library imports
import libJson;
import System.IO.File;

// Project imports
import Scanner;


public object Config {
    public static string Database;
    public static string Host = "127.0.0.1";
    public static string Output;
    public static string Password;
    public static int Port = 3306;
    public static string User;

    public static string toString() const {
        return "Database: '" + Config.Database + "', Host: '" + Config.Host + "', Output: '" + Config.Output + "', User: '" + Config.User + "'";
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

        // Database config
        // {
        Config.Database = Config.Database ?: config[ "Database" ].asString();
        Config.Host     = Config.Host     ?: config[ "Host" ].asString();
        Config.Output   = Config.Output   ?: config[ "Output" ].asString();
        Config.Password = Config.Password ?: config[ "Password" ].asString();
        Config.Port     = Config.Port     ?: cast<int>( config[ "Port" ].asString() );
        Config.User     = Config.User     ?: config[ "User" ].asString();
        // }

        print( Config.toString() );

        return true;
    }

    public void store() {
        var config = new JsonObject();

        // Database config
        // {
        config.addMember( "Database", new JsonValue( Config.Database ) );
        config.addMember( "Host",     new JsonValue( Config.Host ) );
        config.addMember( "Output",   new JsonValue( Config.Output ) );
        config.addMember( "Password", new JsonValue( Config.Password ) );
        config.addMember( "Port",     new JsonValue( Config.Port ) );
        config.addMember( "User",     new JsonValue( Config.User ) );
        // }

        var writer = new JsonStyledWriter();

        var file = new System.IO.File( mFilename, System.IO.File.AccessMode.WriteOnly );
        file.write( writer.toString( config ) );
        file.close();
    }

    private string mFilename const;
}

