
// Library imports
import System.IO.File;
import System.String;

// Project imports
import _config_.Config;
import DatatypeMapper;
import EntityLookup;
import FieldLookup;
import Scanner;
import TemplateLookup;
import TokenLookup;
import Utils;


public object CodeGenerator {
    public void Constructor() {
        mDatabaseHandle = mysql_init();

        mEntityLookup = new EntityLookup();
        mFieldLookup = new FieldLookup();
        mTemplateLookup = new TemplateLookup();
        mTokenLookup = new TokenLookup();
    }

    public void process() modify throws {
        // connect to database
        connect();

        // prepare output folders for lookups, tables and views
        prepareFolders();

        // generate files for all tables
        generateTables();

        // generate files for all views
        generateViews();

        // generate files for all lookups
        generateLookups();

        // disconnect from database
        disconnect();
    }

    private void connect() modify throws {
        mDatabaseHandle = mysql_real_connect( mDatabaseHandle, Config.Host, Config.Port, Config.User, Config.Password, Config.Database );
    
        if ( !mDatabaseHandle ) {
            throw "failed to connect to database '" + Config.Database + "'";
        }
    }

    private void disconnect() modify {
        mysql_close( mDatabaseHandle );
    }

    private string generateLoaders( string entityName, Vector<FieldEntry> fields const, bool usePrimaryKey = true ) const {
        string result;

        foreach ( FieldEntry field : fields ) {
            if ( !usePrimaryKey && field.RealName == PrimaryKeyName ) {
                continue;
            }

            if ( result ) {
                result += LINEBREAK;
            }

            result += MEMBER_LOAD_PREFIX + field.PrettyName + " = cast<" + field.PrettyType + ">( mysql_get_field_value( result, \"" + field.RealName + "\" ) );";
        }

        return result;
    }

    private void generateLookups() modify throws {
        var entities = mEntityLookup.getTables( mDatabaseHandle, Config.Database );
        var baseTemplate = new String( new Scanner( CONFIG_DIRECTORY + "Lookup.txt" ).getText() );

        var libraryImports = LINEBREAK;
        libraryImports += "// import all library files" + LINEBREAK;

        int count;

        foreach ( string name : entities ) {
            var fields = mFieldLookup.getFields( mDatabaseHandle, name );

            bool hasId;
            bool hasToken;

            foreach ( FieldEntry field : fields ) {
                if ( field.RealName == PrimaryKeyName ) {
                    hasId = true;
                }
                else if ( field.RealName == "token" ) {
                    hasToken = true;
                }
            }

            if ( !hasId || !hasToken ) {
                continue;
            }

            var template = copy baseTemplate;

            template.ReplaceAll( TEMPLATE_ENTITY_NAME_PRETTY, Utils.prettify( name ) );        // entity name
            template.ReplaceAll( TEMPLATE_ENUM_DECLARATION, generateEnumMembers( name ) );        // enum declaration list

            var outFile = new System.IO.File( Config.Database + "/Lookups/" + Utils.prettify( name ) + ".os", System.IO.File.AccessMode.WriteOnly );
            outFile.write( cast<string>( template ) );
            outFile.close();

            libraryImports += "import " + Utils.prettify( name ) + ";" + LINEBREAK;

            count++;
        }

        libraryImports += LINEBREAK;

        var allFile = new System.IO.File( Config.Database + "/Lookups/All.os", System.IO.File.AccessMode.WriteOnly );
        allFile.write( libraryImports );
        allFile.close();

        print( "" + count + " lookup objects generated." );
    }

    private string generateEnumMembers( string entityName ) {
        string result;

        int count = -1;
        var tokens = mTokenLookup.getTokens( mDatabaseHandle, Config.Database, entityName );
        var tokenIt = tokens.getIterator();

        while ( tokenIt.hasNext() ) {
            if ( result ) {
                if ( tokenIt.hasNext() ) {
                    result += ",";
                }
                result += LINEBREAK;
            }

            var t = tokenIt.next();
            result += "    " + t.Token + " = " + t.Id;
        }

        return result + ";";
    }

    private string generateMemberDecl( string entityName, Vector<FieldEntry> fields const ) const {
        string result;

        foreach ( FieldEntry field : fields ) {
            if ( result ) {
                result += LINEBREAK;
            }

            result += MEMBER_DECLARATION_PREFIX + field.PrettyType + " " + field.PrettyName + ";";
        }

        return result;
    }

    private string generateMemberList( string entityName, Vector<FieldEntry> fields const, bool usePrimaryKey = true ) const {
        string result;

        foreach ( FieldEntry field : fields ) {
            if ( !usePrimaryKey && field.RealName == PrimaryKeyName ) {
               continue;
            }

            if ( result ) {
                result += ", ";
            }

            result += "`" + field.RealName + "`";
        }

        return result;
    }

    private string generateMemberPairs( string entityName, Vector<FieldEntry> fields const, bool usePrimaryKey = true ) const {
        string result;

        foreach ( FieldEntry field : fields ) {
            if ( !usePrimaryKey && field.RealName == PrimaryKeyName ) {
               continue;
            }

            if ( result ) {
                result += ", ";
            }

            if ( field.RealType == "datetime" || field.RealType == "timestamp" ) {
                result += "`" + field.RealName + "` = NULLIF('\" + " + field.PrettyName + " + \"', '')";
            }
            else {
                result += "`" + field.RealName + "` = '\" + " + field.PrettyName + " + \"'";
            }
        }

        return result;
    }

    private string generateMemberValues( string entityName, Vector<FieldEntry> fields const, bool usePrimaryKey = true ) const {
        string result;

        foreach ( FieldEntry field : fields ) {
            if ( !usePrimaryKey && field.RealName == PrimaryKeyName ) {
               continue;
            }

            if ( result ) {
                result += ", ";
            }

            if ( field.RealType == "datetime" || field.RealType == "timestamp" ) {
                result += "`" + field.RealName + "` = NULLIF('\" + " + field.PrettyName + " + \"', '')";
            }
            else {
                result += "'\" + " + field.PrettyName + " + \"'";
            }
        }

        return result;
    }

    private void generateTables() modify {
        var entities = mEntityLookup.getTables( mDatabaseHandle, Config.Database );
        var baseTemplate = new String( new Scanner( CONFIG_DIRECTORY + "Table.txt" ).getText() );

        var libraryImports = LINEBREAK;
        libraryImports += "// import all library files" + LINEBREAK;

        int count;
        foreach ( string name : entities ) {
            var template = copy baseTemplate;

            replaceSpecialTemplates( template, name );
            replaceUserTemplates( template );
    
            var outFile = new System.IO.File( Config.Database + "/Tables/" + Utils.prettify( name ) + ".os", System.IO.File.AccessMode.WriteOnly );
            outFile.write( cast<string>( template ) );
            outFile.close();

            libraryImports += "import " + Utils.prettify( name ) + ";" + LINEBREAK;

            count++;
        }

        libraryImports += LINEBREAK;

        var allFile = new System.IO.File( Config.Database + "/Tables/All.os", System.IO.File.AccessMode.WriteOnly );
        allFile.write( libraryImports );
        allFile.close();

        print( "" + count + " table objects generated." );
    }

    private string generateUpdates( string entityName, Vector<FieldEntry> fields, bool usePrimaryKey = true ) const {
        return MEMBER_LOAD_PREFIX + "// UPDATE: not yet implemented";
    }

    private void generateViews() modify {
        var entities = mEntityLookup.getViews( mDatabaseHandle, Config.Database );
        var baseTemplate = new String( new Scanner( CONFIG_DIRECTORY + "View.txt" ).getText() );

        var libraryImports = LINEBREAK;
        libraryImports += "// import all library files" + LINEBREAK;

        int count;
        foreach ( string name : entities ) {
            var template = copy baseTemplate;

            replaceSpecialTemplates( template, name );
            replaceUserTemplates( template );

            var outFile = new System.IO.File( Config.Database + "/Views/" + Utils.prettify( name ) + ".os", System.IO.File.AccessMode.WriteOnly );
            outFile.write( cast<string>( template ) );
            outFile.close();

            libraryImports += "import " + Utils.prettify( name ) + ";" + LINEBREAK;

            count++;
        }

        libraryImports += LINEBREAK;

        var allFile = new System.IO.File( Config.Database + "/Views/All.os", System.IO.File.AccessMode.WriteOnly );
        allFile.write( libraryImports );
        allFile.close();

        print( "" + count + " view objects generated." );
    }

    private void prepareFolders() modify {
        system( "mkdir -p " + Config.Output + "/Lookups" );
        system( "mkdir -p " + Config.Output + "/Tables" );
        system( "mkdir -p " + Config.Output + "/Views" );
    }

    private void replaceSpecialTemplates( String template, string name ) modify {
        var fields = mFieldLookup.getFields( mDatabaseHandle, name );

        string primaryKeyType;
        foreach ( FieldEntry field : fields ) {
            if ( field.RealName == PrimaryKeyName ) {
                primaryKeyType = field.PrettyType;
                break;
            }
        }

        template.ReplaceAll( TEMPLATE_ENTITY_NAME,                 name );                                          // name
        template.ReplaceAll( TEMPLATE_ENTITY_NAME_PRETTY,          Utils.prettify( name ) );                        // pretty printed name
        template.ReplaceAll( TEMPLATE_ENTITY_NAME_UPPERCASE,       toUpper( name ) );                               // name in upper case
        template.ReplaceAll( TEMPLATE_MEMBER_DECLARATION,          generateMemberDecl( name, fields ) );            // members
        template.ReplaceAll( TEMPLATE_MEMBER_LIST,                 generateMemberList( name, fields, true ) );      // member list
        template.ReplaceAll( TEMPLATE_MEMBER_LOAD,                 generateLoaders( name, fields, true ) );         // loaders
        template.ReplaceAll( TEMPLATE_MEMBER_PAIR,                 generateMemberPairs( name, fields, true ) );     // key values pairs
        template.ReplaceAll( TEMPLATE_MEMBER_PAIR_WITHOUT_PRIMARY, generateMemberPairs( name, fields, false ) );    // key values pairs without primary key
        template.ReplaceAll( TEMPLATE_MEMBER_UPDATE,               generateUpdates( name, fields, false ) );        // updates
        template.ReplaceAll( TEMPLATE_MEMBER_VALUES,               generateMemberValues( name, fields, true ) );    // values
        template.ReplaceAll( TEMPLATE_PRIMARY_KEY_NAME,            PrimaryKeyName );                                // primary key name
        template.ReplaceAll( TEMPLATE_PRIMARY_KEY_NAME_PRETTY,     Utils.prettify( PrimaryKeyName ) );              // primary key pretty printed name
        template.ReplaceAll( TEMPLATE_PRIMARY_KEY_TYPE,            primaryKeyType );                                // primary key type
    }

    private void replaceUserTemplates( String template ) modify {
        foreach ( Pair<string, string> p : mTemplateLookup ) {
            //print( "Replacing template '" + p.first + "' with '" + p.second + "'" );

            template.ReplaceAll( p.first, p.second );
        }
    }

    private int mDatabaseHandle;
    private EntityLookup mEntityLookup;
    private FieldLookup mFieldLookup;
    private TemplateLookup mTemplateLookup;
    private TokenLookup mTokenLookup;
}

