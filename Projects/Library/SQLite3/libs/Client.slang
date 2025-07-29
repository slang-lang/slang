#!/usr/bin/env slang

// library imports
import libParam;
import libSQLite3;
import libSQLite3.Exceptions;

// project imports
import Consts;
import Settings;


public object Client
{
	public void Constructor( string filename ) {
		settings = new Settings();

		if ( filename ) {
			open( filename );
		}
	}

	public int Run() modify {
		print( "libSQLite version " + SQLITE_VERSION );
		print( "Enter \".help\" for usage hints." );

		if ( !database ) {
			// print( "Connected to a transient in-memory database." );
			print( "Use \".open FILENAME\" to reopen on a persistent database." );
		}

		while ( true ) {
			write( "sqlite> " );

			var input = new String( cin() );

			if ( settings.Echo ) {
				print( cast<string>( input ) );
			}

			var tokenIt = input.SplitBy( " " );
			if ( tokenIt.hasNext() ) {
				var command = tokenIt++;

				if ( command == ".echo" ) {
					string echo;
					if ( tokenIt.hasNext() && (tokenIt++) == "on" ) {
						echo = true;
					}

					settings.Echo = echo;
				}
				else if ( command == ".exit" ) {
					int exitCode;
					if ( tokenIt.hasNext() ) {
						exitCode = cast<int>( tokenIt++ );
					}

					return exitCode;
				}
				else if ( command == ".help" ) {
					printHelp();
				}
				else if ( command == ".open" ) {
					string filename;

					if ( tokenIt.hasNext() ) {
						filename = tokenIt++;
					}

					open( filename );
				}
				else if ( command == ".quit" ) {
					return 0;
				}
				else if ( command == ".tables" ) {
					printTables();
				}
				else if ( command == ".version" ) {
					print( APPNAME + " " + VERSION );
					print( "libSQLite version " + SQLITE_VERSION );
				}
				else if ( input.StartsWith( "." ) ) {
					print( "unsupported command: " + cast<string>( input ) );
				}
				else {
					if ( database ) {
						query( cast<string>( input ) );

						continue;
					}

					print( "You need to open/load a database first." );
				}
			}
		}

		return -1;
	}

	private void open( string filename ) modify {
		database = new Sqlite3Database( filename );
	}

	private void printHelp() {
		print( "
.echo on|off             Turn command echo on or off
.exit ?CODE?             Exit this program with return-code CODE
.explain ?on|off|auto?   Change the EXPLAIN formatting mode.  Default: auto
.headers on|off          Turn display of headers on or off
.help ?-all? ?PATTERN?   Show help text for PATTERN
.open ?OPTIONS? ?FILE?   Close existing database and reopen FILE
.quit                    Stop interpreting input stream, exit if primary.
.tables ?TABLE?          List names of tables matching LIKE pattern TABLE
.version                 Show source, library and compiler versions
		" );

//.archive ...             Manage SQL archives
//.auth ON|OFF             Show authorizer callbacks
//.backup ?DB? FILE        Backup DB (default \"main\") to FILE
//.bail on|off             Stop after hitting an error.  Default OFF
//.cd DIRECTORY            Change the working directory to DIRECTORY
//.changes on|off          Show number of rows changed by SQL
//.check GLOB              Fail if output since .testcase does not match
//.clone NEWDB             Clone data into NEWDB from the existing database
//.connection [close] [#]  Open or close an auxiliary database connection
//.databases               List names and files of attached databases
//.dbconfig ?op? ?val?     List or change sqlite3_db_config() options
//.dbinfo ?DB?             Show status information about the database
//.dump ?OBJECTS?          Render database content as SQL
//.eqp on|off|full|...     Enable or disable automatic EXPLAIN QUERY PLAN
//.excel                   Display the output of next command in spreadsheet
//.expert                  EXPERIMENTAL. Suggest indexes for queries
//.filectrl CMD ...        Run various sqlite3_file_control() operations
//.fullschema ?--indent?   Show schema and the content of sqlite_stat tables
//.import FILE TABLE       Import data from FILE into TABLE
//.indexes ?TABLE?         Show names of indexes
//.limit ?LIMIT? ?VAL?     Display or change the value of an SQLITE_LIMIT
//.lint OPTIONS            Report potential schema issues.
//.load FILE ?ENTRY?       Load an extension library
//.log FILE|on|off         Turn logging on or off.  FILE can be stderr/stdout
//.mode MODE ?OPTIONS?     Set output mode
//.nonce STRING            Suspend safe mode for one command if nonce matches
//.nullvalue STRING        Use STRING in place of NULL values
//.once ?OPTIONS? ?FILE?   Output for the next SQL command only to FILE
//.output ?FILE?           Send output to FILE or stdout if FILE is omitted
//.parameter CMD ...       Manage SQL parameter bindings
//.print STRING...         Print literal STRING
//.progress N              Invoke progress handler after every N opcodes
//.prompt MAIN CONTINUE    Replace the standard prompts
//.read FILE               Read input from FILE or command output
//.recover                 Recover as much data as possible from corrupt db.
//.restore ?DB? FILE       Restore content of DB (default \"main\") from FILE
//.save ?OPTIONS? FILE     Write database to FILE (an alias for .backup ...)
//.scanstats on|off|est    Turn sqlite3_stmt_scanstatus() metrics on or off
//.schema ?PATTERN?        Show the CREATE statements matching PATTERN
//.separator COL ?ROW?     Change the column and row separators
//.session ?NAME? CMD ...  Create or control sessions
//.sha3sum ...             Compute a SHA3 hash of database content
//.shell CMD ARGS...       Run CMD ARGS... in a system shell
//.show                    Show the current values for various settings
//.stats ?ARG?             Show stats or turn stats on or off
//.system CMD ARGS...      Run CMD ARGS... in a system shell
//.timeout MS              Try opening locked tables for MS milliseconds
//.timer on|off            Turn SQL timer on or off
//.trace ?OPTIONS?         Output each SQL statement as it is run
//.vfsinfo ?AUX?           Information about the top-level VFS
//.vfslist                 List all available VFSes
//.vfsname ?AUX?           Print the name of the VFS stack
//.width NUM1 NUM2 ...     Set minimum column widths for columnar output
	}

	private void printTables() {
		if ( !database ) {
			print( "You need to open/load a database first." );
			return;
		}

		var result = database.exec( "SELECT name FROM sqlite_master WHERE type = 'table'" );

		if ( database.errCode() ) {
			print( "Error: " + database.errMsg() );
		}
		else {
			print( "Tables:" );

			foreach ( Sqlite3Row row : result ) {
				foreach ( Sqlite3Entry entry : row ) {
					print( "   " + entry.Value );
				}
			}
		}
	}

	private void query( string command ) modify {
		try {
			var result = database.exec( command );

			int rowIdx;

			foreach ( Sqlite3Row row : result ) {
				string line;

				int entryIdx;
				foreach ( Sqlite3Entry e : row ) {
					if ( line ) {
						line += "|";
					}
					line += e.Value;

					entryIdx++;
				}

				print( "|" + line + "|" );

				rowIdx++;
			}
		}
		catch ( string e ) {
			print( "Error: " + e );
		}
		catch ( IException e ) {
			print( "Error: " + e.what() );
		}
	}

	private Sqlite3Database database;
	private Settings settings;
}

