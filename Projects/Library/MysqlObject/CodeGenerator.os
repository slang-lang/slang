
// Library imports
import System.IO.File;
import System.String;

// Project imports
import ConfigLoader;
import DatatypeMapper;
import EntityLookup;
import FieldLookup;


public object CodeGenerator {
    public void Constructor() {
        mConfig = new ConfigLoader( Database + "/config.json" );
        mConfig.load();

        mDBHandle = mysql_init();
    }

    public void process() modify throws {
        // connect to database
        connect();

        // prepare output folders
        prepareFolders();

        // query entities
        var lookup = new EntityLookup();

        // generate tables
        {
            var entities = lookup.getTables( mDBHandle, Database );

            int count;
            foreach ( string entityName : entities ) {
                generateEntity( entityName, "Table" );

                count++;
            }

            print( "" + count + " table objects generated." );
        }

        // generate views
        {
            var entities = lookup.getViews( mDBHandle, Database );

            int count;
            foreach ( string entityName : entities ) {
                generateEntity( entityName, "View" );

                count++;
            }

            print( "" + count + " view objects generated." );
        }

        // disconnect from database
        disconnect();

        // store configuration
        //mConfig.store();
    }

    private void connect() modify throws {
        mDBHandle = mysql_real_connect( mDBHandle, Host, Port, User, Password, Database );
    
        if ( !mDBHandle ) {
            throw "failed to connect to database '" + Database + "'";
        }
    }

    private void disconnect() modify {
        mysql_close( mDBHandle );
    }

    private void generateEntity( string name, string entityType ) modify {
        var fieldLookup = new FieldLookup();

        var entity = fieldLookup.getFields( mDBHandle, name );
        var template = new String( readFile( entityType + ".txt") );

        template.ReplaceAll( TEMPLATE_ENTITY_NAME,              name );                                 // name
        template.ReplaceAll( TEMPLATE_ENTITY_NAME_UPPERCASE,    toUpper(name) );                        // name in upper case
        template.ReplaceAll( TEMPLATE_ENTITY_POSTFIX,           TABLE_POSTFIX );                        // postfix
        template.ReplaceAll( TEMPLATE_ENTITY_PREFIX,            TABLE_PREFIX );                         // prefix
        template.ReplaceAll( TEMPLATE_IMPORT,                   generateImports( name, entity ) );      // imports
        template.ReplaceAll( TEMPLATE_MEMBER_DECLARATION,       generateMemberDecl( name, entity ) );   // members
        template.ReplaceAll( TEMPLATE_MEMBER_INSERT,            generateInserts( name, entity ) );      // inserts
        template.ReplaceAll( TEMPLATE_MEMBER_LIST,              generateMemberList( name, entity ) );   // member list
        template.ReplaceAll( TEMPLATE_MEMBER_LOAD,              generateLoaders( name, entity ) );      // loaders
        template.ReplaceAll( TEMPLATE_MEMBER_UPDATE,            generateUpdates( name, entity ) );      // updates
        template.ReplaceAll( TEMPLATE_MEMBER_VALUES,            generateMemberValues( name, entity ) ); // values
        template.ReplaceAll( TEMPLATE_PRIMARY_KEY,              PrimaryKeyName );                       // values

        var outFile = new System.IO.File( Database + "/" + entityType + "s/" + toUpper(name) + ".os", System.IO.File.AccessMode.WriteOnly );
        outFile.write( cast<string>( template ) );
        outFile.close();
    }

    private unstable string generateImports( string entityName, Map<string, string> entity ) const {
        return "// IMPORT: not yet implemented";
    }

    private unstable string generateInserts( string entityName, Map<string, string> entity ) const {
        string fields;
        foreach ( Pair<string, string> field : entity ) {
            if ( fields ) {
                fields += ", ";
            }

            fields += field.first;
        }

        string values;
        foreach ( Pair<string, string> field : entity ) {
            if ( values ) {
                values += ",";
            }

            values += "\" + " + field.first + " + \"";
        }

        return MEMBER_LOAD_PREFIX + "INSERT INTO " + entityName + " ( " + fields + " ) VALUES ( " + values + " )";
    }

    private string generateLoaders( string entityName, Map<string, string> entity ) const {
        string loaders;

        var it = entity.getIterator();
        while ( it.hasNext() ) {
            var field = Pair<string, string> it.next();

            if ( field.first == PrimaryKeyName ) {
                continue;
            }

            loaders += MEMBER_LOAD_PREFIX + field.first + " = cast<" + field.second + ">( mysql_get_field_value( result, \"" + field.first + "\" ) );";
            if ( it.hasNext() ) {
                loaders += LINEBREAK;
            }
        }

        return loaders;
    }

    private string generateMemberDecl( string entityName, Map<string, string> entity ) const {
        string members;

        var it = entity.getIterator();
        while ( it.hasNext() ) {
            var field = Pair<string, string> it.next();

            members += MEMBER_DECLARATION_PREFIX + field.second + " " + field.first + ";";
            if ( it.hasNext() ) {
                members += LINEBREAK;
            }
        }

        return members;
    }

    private string generateMemberList( string entityName, Map<string, string> entity ) const {
        string fields;

        foreach ( Pair<string, string> field : entity ) {
            if ( field.first == PrimaryKeyName ) {
               continue;
            }

            if ( fields ) {
                fields += ", ";
            }

            fields += field.first;
        }

        return fields;
    }

    private string generateMemberValues( string entityName, Map<string, string> entity ) const {
        string fields;

        foreach ( Pair<string, string> field : entity ) {
            if ( field.first == PrimaryKeyName ) {
               continue;
            }

            if ( fields ) {
                fields += ", ";
            }

            fields += "'\" + " + field.first + " + \"'";
        }

        return fields;
    }

    private unstable string generateUpdates( string entityName, Map<string, string> entity ) const {
        return MEMBER_LOAD_PREFIX + "// UPDATE: not yet implemented";
    }

    private void prepareFolders() modify {
        system( "mkdir -p " + Output + "/Tables" );
        system( "mkdir -p " + Output + "/Views" );
    }

    private string readFile( string filename ) const {
        var file = new System.IO.File( filename, System.IO.File.AccessMode.ReadOnly );

        string text;
        while ( !file.isEOF() ) {
            text += file.readChar();
        }

        return text;
    }

    private ConfigLoader mConfig;
    private int mDBHandle;
}
