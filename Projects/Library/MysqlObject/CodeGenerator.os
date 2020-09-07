
// Library imports
import System.IO.File;
import System.String;

// Project imports
import _config_.Config;
import ConfigLoader;
import DatatypeMapper;
import EntityLookup;
import FieldLookup;
import Scanner;
import TemplateLookup;


public object CodeGenerator {
    public void Constructor() {
        mConfig = new ConfigLoader( Database + "/config.json" );
        mConfig.load();

        mDatabaseHandle = mysql_init();

        mEntityLookup = new EntityLookup();
        mFieldLookup = new FieldLookup();
        mTemplateLookup = new TemplateLookup();
    }

    public void process() modify throws {
        // connect to database
        connect();

        // prepare output folders
        prepareFolders();

        // generate tables
        generateTables();

        // generate views
        generateViews();

        // disconnect from database
        disconnect();

        // store configuration
        //mConfig.store();
    }

    private void connect() modify throws {
        mDatabaseHandle = mysql_real_connect( mDatabaseHandle, Host, Port, User, Password, Database );
    
        if ( !mDatabaseHandle ) {
            throw "failed to connect to database '" + Database + "'";
        }
    }

    private void disconnect() modify {
        mysql_close( mDatabaseHandle );
    }

    private string generateLoaders( string entityName, Map<string, string> fields const ) const {
        string result;

        foreach ( Pair<string, string> field : fields ) {
/*
            if ( field.first == PrimaryKeyName ) {
                continue;
            }
*/

            if ( result ) {
                result += LINEBREAK;
            }

            result += MEMBER_LOAD_PREFIX + field.first + " = cast<" + field.second + ">( mysql_get_field_value( result, \"" + field.first + "\" ) );";
        }

        return result;
    }

    private string generateMemberDecl( string entityName, Map<string, string> fields const ) const {
        string result;

        foreach ( Pair<string, string> field : fields ) {
            if ( result ) {
                result += LINEBREAK;
            }

            result += MEMBER_DECLARATION_PREFIX + field.second + " " + field.first + ";";
        }

        return result;
    }

    private string generateMemberList( string entityName, Map<string, string> fields const ) const {
        string result;

        foreach ( Pair<string, string> field : fields ) {
/*
            if ( field.first == PrimaryKeyName ) {
               continue;
            }
*/

            if ( result ) {
                result += ", ";
            }

            result += field.first;
        }

        return result;
    }

    private string generateMemberValues( string entityName, Map<string, string> fields const ) const {
        string result;

        foreach ( Pair<string, string> field : fields ) {
/*
            if ( field.first == PrimaryKeyName ) {
               continue;
            }
*/

            if ( result ) {
                result += ", ";
            }

            result += "'\" + " + field.first + " + \"'";
        }

        return result;
    }

    private void generateTables() modify {
        var entities = mEntityLookup.getTables( mDatabaseHandle, Database );
        var baseTemplate = new String( new Scanner( CONFIG_DIRECTORY + "Table.txt" ).getText() );

        int count;
        foreach ( string name : entities ) {
            var template = copy baseTemplate;

            replaceSpecialTemplates( template, name );
            replaceUserTemplates( template );
    
            var outFile = new System.IO.File( Database + "/Tables/" + toUpper( name ) + ".os", System.IO.File.AccessMode.WriteOnly );
            outFile.write( cast<string>( template ) );
            outFile.close();

            count++;
        }

        print( "" + count + " table objects generated." );
    }

    private unstable string generateUpdates( string entityName, Map<string, string> fields ) const {
        return MEMBER_LOAD_PREFIX + "// UPDATE: not yet implemented";
    }

    private void generateViews() modify {
        var entities = mEntityLookup.getViews( mDatabaseHandle, Database );
        var fieldLookup = new FieldLookup();
        var baseTemplate = new String( new Scanner( CONFIG_DIRECTORY + "View.txt" ).getText() );

        int count;
        foreach ( string name : entities ) {
            var template = copy baseTemplate;

            replaceSpecialTemplates( template, name );
            replaceUserTemplates( template );
    
            var outFile = new System.IO.File( Database + "/Views/" + toUpper( name ) + ".os", System.IO.File.AccessMode.WriteOnly );
            outFile.write( cast<string>( template ) );
            outFile.close();

            count++;
        }

        print( "" + count + " view objects generated." );
    }

    private void prepareFolders() modify {
        system( "mkdir -p " + Output + "/Tables" );
        system( "mkdir -p " + Output + "/Views" );
    }

    private void replaceSpecialTemplates( String template, string name ) modify {
        var fields = mFieldLookup.getFields( mDatabaseHandle, name );

        template.ReplaceAll( TEMPLATE_ENTITY_NAME,              name );                                 // name
        template.ReplaceAll( TEMPLATE_ENTITY_NAME_UPPERCASE,    toUpper( name ) );                      // name in upper case
        template.ReplaceAll( TEMPLATE_MEMBER_DECLARATION,       generateMemberDecl( name, fields ) );   // members
        template.ReplaceAll( TEMPLATE_MEMBER_LIST,              generateMemberList( name, fields ) );   // member list
        template.ReplaceAll( TEMPLATE_MEMBER_LOAD,              generateLoaders( name, fields ) );      // loaders
        template.ReplaceAll( TEMPLATE_MEMBER_UPDATE,            generateUpdates( name, fields ) );      // updates
        template.ReplaceAll( TEMPLATE_MEMBER_VALUES,            generateMemberValues( name, fields ) ); // values
    }

    private void replaceUserTemplates( String template ) modify {
        foreach ( Pair<string, string> p : mTemplateLookup ) {
            //print( "Replacing template '" + p.first + "' with '" + p.second + "'" );

            template.ReplaceAll( p.first, p.second );
        }
    }

    private ConfigLoader mConfig;
    private int mDatabaseHandle;
    private EntityLookup mEntityLookup;
    private FieldLookup mFieldLookup;
    private TemplateLookup mTemplateLookup;
}
