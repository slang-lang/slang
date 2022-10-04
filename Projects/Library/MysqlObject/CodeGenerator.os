
// Library imports
import System.IO.File;
import System.String;

// Project imports
import _config_.Config;
import EntityLookup;
import Scanner;
import TemplateLookup;
import Utils;


public object CodeGenerator {
    public void process() modify throws {
        // connect to database
        connect();

        mEntityLookup = new EntityLookup( mDatabaseHandle, Config.Database );
        mEntityLookup.fetchEntities();

        mTemplateLookup = new TemplateLookup();
        mTemplateLookup.fetchTemplates();

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
        mDatabaseHandle = mysql_init();
        mDatabaseHandle = mysql_real_connect( mDatabaseHandle, Config.Host, Config.Port, Config.User, Config.Password, Config.Database );
    
        if ( !mDatabaseHandle ) {
            throw "failed to connect to database '" + Config.Database + "'";
        }
    }

    private void disconnect() modify throws {
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
        var entities = mEntityLookup.getTables();
        var baseTemplate = new String( new Scanner( CONFIG_DIRECTORY + "Lookup.txt" ).getText() );

        var libraryImports = LINEBREAK;
        libraryImports += "// import all library files" + LINEBREAK;

        int count;
        foreach ( Pair<string, EntityType> entity : entities ) {
            if ( !entity.second.HasLookup ) {
                continue;
            }

            var template = copy baseTemplate;

            template.ReplaceAll( TEMPLATE_ENTITY_NAME_PRETTY, Utils.prettify( entity.first ) );        // entity name
            template.ReplaceAll( TEMPLATE_ENUM_DECLARATION, generateEnumMembers( entity.second ) );        // enum declaration list

            var outFile = new System.IO.File( Config.Output + "/Lookups/" + Utils.prettify( entity.first ) + ".os", System.IO.File.AccessMode.WriteOnly );
            outFile.write( cast<string>( template ) );
            outFile.close();

            libraryImports += "import " + Utils.prettify( entity.first ) + ";" + LINEBREAK;

            count++;
        }

        libraryImports += LINEBREAK;

        var allFile = new System.IO.File( Config.Output + "/Lookups/All.os", System.IO.File.AccessMode.WriteOnly );
        allFile.write( libraryImports );
        allFile.close();

        print( "" + count + " lookup objects generated." );

        if ( count > 0 ) {
            // prepare key lookup object
            var keyLookupTemplate = new String( new Scanner( CONFIG_DIRECTORY + "KeyLookup.txt" ).getText() );

            replaceUserTemplates( keyLookupTemplate );

            var outFile = new System.IO.File( Config.Output + "/KeyLookup.os", System.IO.File.AccessMode.WriteOnly );
            outFile.write( cast<string>( keyLookupTemplate ) );
            outFile.close();
        }
    }

    private string generateEnumMembers( EntityType entity ) {
        string result;

        var tokenIt = entity.Tokens.getIterator();
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
                result += "NULLIF('\" + " + field.PrettyName + " + \"', '')";
            }
            else {
                result += "'\" + " + field.PrettyName + " + \"'";
            }
        }

        return result;
    }

    private void generateTables() modify {
        var entities = mEntityLookup.getTables();

        var baseTemplateWithId    = new String( new Scanner( CONFIG_DIRECTORY + "table_with_id.txt" ).getText() );
        var baseTemplateWithoutId = new String( new Scanner( CONFIG_DIRECTORY + "table_without_id.txt" ).getText() );

        var libraryImports = LINEBREAK;
        libraryImports += "// import all library files" + LINEBREAK;

        var idField = new FieldEntry( PrimaryKeyName, "Id", "int", "int" );

        int count;
        foreach ( Pair<string, EntityType> entity : entities ) {
            String template;

            if ( entity.second.Fields.indexOf( idField ) >= 0 ) {
               template = copy baseTemplateWithId;
            }
            else {
               template = copy baseTemplateWithoutId;
            }

            replaceSpecialTemplates( template, entity.second );
            replaceUserTemplates( template );

            var outFile = new System.IO.File( Config.Output + "/Tables/" + Utils.prettify( entity.first ) + ".os", System.IO.File.AccessMode.WriteOnly );
            outFile.write( cast<string>( template ) );
            outFile.close();

            libraryImports += "import " + Utils.prettify( entity.first ) + ";" + LINEBREAK;

            count++;
        }

        libraryImports += LINEBREAK;

        var allFile = new System.IO.File( Config.Output + "/Tables/All.os", System.IO.File.AccessMode.WriteOnly );
        allFile.write( libraryImports );
        allFile.close();

        print( "" + count + " table objects generated." );
    }

    private string generateUpdates( string entityName, Vector<FieldEntry> fields, bool usePrimaryKey = true ) const {
        return MEMBER_LOAD_PREFIX + "// UPDATE: not yet implemented";
    }

    private void generateViews() modify {
        var entities = mEntityLookup.getViews();

        var baseTemplateWithId    = new String( new Scanner( CONFIG_DIRECTORY + "view_with_id.txt" ).getText() );
        var baseTemplateWithoutId = new String( new Scanner( CONFIG_DIRECTORY + "view_without_id.txt" ).getText() );

        var libraryImports = LINEBREAK;
        libraryImports += "// import all library files" + LINEBREAK;

        var idField = new FieldEntry( PrimaryKeyName, "Id", "int", "int" );

        int count;
        foreach ( Pair<string, EntityType> entity : entities ) {
            String template;

            if ( entity.second.Fields.indexOf( idField ) >= 0 ) {
                template = copy baseTemplateWithId;
            }
            else {
                template = copy baseTemplateWithoutId;
            }

            replaceSpecialTemplates( template, entity.second );
            replaceUserTemplates( template );

            var outFile = new System.IO.File( Config.Output + "/Views/" + Utils.prettify( entity.first ) + ".os", System.IO.File.AccessMode.WriteOnly );
            outFile.write( cast<string>( template ) );
            outFile.close();

            libraryImports += "import " + Utils.prettify( entity.first ) + ";" + LINEBREAK;

            count++;
        }

        libraryImports += LINEBREAK;

        var allFile = new System.IO.File( Config.Output + "/Views/All.os", System.IO.File.AccessMode.WriteOnly );
        allFile.write( libraryImports );
        allFile.close();

        print( "" + count + " view objects generated." );
    }

    private void prepareFolders() modify {
        system( "mkdir -p " + Config.Output + "/Lookups" );
        system( "mkdir -p " + Config.Output + "/Tables" );
        system( "mkdir -p " + Config.Output + "/Views" );
    }

    private void replaceSpecialTemplates( String template, EntityType entity ) modify {
        var fields = entity.Fields;

        string primaryKeyType;
        foreach ( FieldEntry field : fields ) {
            if ( field.RealName == PrimaryKeyName ) {
                primaryKeyType = field.PrettyType;
                break;
            }
        }

        template.ReplaceAll( TEMPLATE_ENTITY_NAME,                 entity.Name );                                          // name
        template.ReplaceAll( TEMPLATE_ENTITY_NAME_PRETTY,          Utils.prettify( entity.Name ) );                        // pretty printed name
        template.ReplaceAll( TEMPLATE_ENTITY_NAME_UPPERCASE,       toUpper( entity.Name ) );                               // name in upper case
        template.ReplaceAll( TEMPLATE_MEMBER_DECLARATION,          generateMemberDecl( entity.Name, fields ) );            // members
        template.ReplaceAll( TEMPLATE_MEMBER_LIST,                 generateMemberList( entity.Name, fields, true ) );      // member list
        template.ReplaceAll( TEMPLATE_MEMBER_LOAD,                 generateLoaders( entity.Name, fields, true ) );         // loaders
        template.ReplaceAll( TEMPLATE_MEMBER_PAIR,                 generateMemberPairs( entity.Name, fields, true ) );     // key values pairs
        template.ReplaceAll( TEMPLATE_MEMBER_PAIR_WITHOUT_PRIMARY, generateMemberPairs( entity.Name, fields, false ) );    // key values pairs without primary key
        template.ReplaceAll( TEMPLATE_MEMBER_UPDATE,               generateUpdates( entity.Name, fields, false ) );        // updates
        template.ReplaceAll( TEMPLATE_MEMBER_VALUES,               generateMemberValues( entity.Name, fields, true ) );    // values
        template.ReplaceAll( TEMPLATE_PRIMARY_KEY_NAME,            PrimaryKeyName );                                       // primary key name
        template.ReplaceAll( TEMPLATE_PRIMARY_KEY_NAME_PRETTY,     Utils.prettify( PrimaryKeyName ) );                     // primary key pretty printed name
        template.ReplaceAll( TEMPLATE_PRIMARY_KEY_TYPE,            primaryKeyType );                                       // primary key type
    }

    private void replaceUserTemplates( String template ) modify {
        foreach ( Pair<string, string> p : mTemplateLookup ) {
            template.ReplaceAll( p.first, p.second );
        }
    }

    private int mDatabaseHandle;
    private EntityLookup mEntityLookup;
    private TemplateLookup mTemplateLookup;
}

