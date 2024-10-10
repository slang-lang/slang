
// library imports
import libParam;
import System.String;

// project imports
import QueryExecutor;


public object App
{
    public void Constructor() {
        loadTables();
    }

    public void Run() modify {
        while ( true ) {
            write( PROMPT << "> " );

            var command = cin();

            switch ( command ) {
                case "explain table": { print( "explain table <table>" ); break; }
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
        //print( "Execute query '" + query + "'" );

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

    private void loadTables() modify throws {
        print( "Loading tables..." );

        Tables = new Vector<string>();

        var tableIt = new String( system( "ls *.csv" ) ).SplitBy( LINEBREAK );
        while( tableIt.hasNext() ) {
            var table = tableIt.next();
            if ( !table ) {
                break;
            }

            print( "Table: " + table );

            Tables.push_back( table );
        }
    }

    private void printHelp() const {
        print( "explain table   reload all CSV tables" );
        print( "help            this screen" );
        print( "load tables     reload all CSV tables" );
        print( "quit            end csvdb session" );
        print( "show tables     display all known CSV tables" );
    }

    private void showTables() const {
        foreach ( string table : Tables ) {
            print( table );
        }
    }

    // consts
    private string PROMPT const = "csvdb";

    // members
    private Map<string, CSVReader> TableData;
    private Vector<string> Tables;
}
