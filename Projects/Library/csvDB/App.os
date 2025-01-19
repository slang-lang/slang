
// library imports
import libParam;
import System.String;

// project imports
import QueryExecutor;


public object App
{
    public void Constructor( ParameterHandler params ) {
        loadTables();

        Params     = params;
        SilentMode = params.size();
    }

    public void Run() modify {
        if ( Params.size() ) {
           executeQuery( Params[ 0 ].Key );

           return;
        }

        while ( true ) {
            write( PROMPT << "> " );

            var command = cin();

            switch ( command ) {
                case "h":             { printHelp(); break; }
                case "help":          { printHelp(); break; }
                case "load tables":   { loadTables(); break; }
                case "show tables":   { showTables(); break; }
                case "quit":          { print( "Exiting csvdb session..." ); return; }
                default:              { executeQuery( command ); break; }
            }
        }

        return;
    }

    private void executeQuery( string query ) modify {
        try {
            var executor = new QueryExecutor();
            executor.exec( query );
        }
        catch ( string e ) {
            print( "[Error] " + e );
        }
        catch ( IException e ) {
            print( "[Error] " + e.what() );
        }
    }

    private void explainTable( string table ) modify {
        table = expandTableName( table );

        var data const = TableData[ table ];

        print( cast<string>( data[ 0 ] ) );
    }

    private void loadTables() modify throws {
        if( !SilentMode ) {
            print( "Loading tables..." );
        }

        TableData = new Map<string, CSVReader>();

        var tableIt = new String( system( "ls *.csv" ) ).SplitBy( LINEBREAK );
        while( tableIt.hasNext() ) {
            var table = tableIt.next();
            if ( !table ) {
                break;
            }

            try {
                TableData.insert( table, new CSVReader( table, true ) );
            }
        }

        showTables();
    }

    private void printHelp() const {
        print( "explain <table>   explain given table" );
        print( "help              this screen" );
        print( "load tables       reload all CSV tables" );
        print( "quit              end csvdb session" );
        print( "select <columns> from <table> [where <condition>] [limit <limit>]            execute query" );
        print( "show tables       display all known tables" );
    }

    private void showTables() const {
        foreach ( Pair<string, CSVReader> table : TableData ) {
            print( "Table: " + table.first );
        }
    }

    private void useFolder( string folder ) modify {
        Folder = folder;

        loadTables();
    }

    // consts
    private string PROMPT const = "csvdb";

    // members
    private string Folder;
    private ParameterHandler Params;
    private bool SilentMode;
    private Map<string, CSVReader> TableData;
}
