#!/usr/local/bin/oscript

// Library imports
import libParam.ParameterHandler;
import System.IO.File;

// Project imports
import ConfigLoader;
import DatatypeMapper;
import Generator;
import Lookup;


public void Main( int argc, string args ) modify throws {
	var params = new ParameterHandler( argc, args );

	if ( !params.contains( "database" ) ) {
		print( "database missing!" );
		exit( -1 );
	}

	if ( params.contains( "database" ) ) {
		Database = params.getParameter( "database" ).Value;
	}
	if ( params.contains( "host" ) ) {
		Host = params.getParameter( "host" ).Value;
	}
	if ( params.contains( "password" ) ) {
		Password = params.getParameter( "password" ).Value;
	}
	if ( params.contains( "port" ) ) {
		Port = cast<int>( params.getParameter( "port" ).Value );
	}
	if ( params.contains( "user" ) ) {
		User = params.getParameter( "user" ).Value;
	}

	try {
		var configLoader = new ConfigLoader( "config.json" );
		configLoader.load();
		configLoader.store();

		int DBHandle = connect();

		var lookup = new Lookup( DBHandle );

		prepareFolders();

		// generate tables
		{
			var tables = lookup.getTables( Database );

			int count;
			foreach ( string tableName : tables ) {
				generateTable( DBHandle, tableName );

				count++;
			}

			print( "" + count + " table objects generated." );
		}

		// generate views
		{
			var views = lookup.getViews( Database );

			int count;
			foreach ( string tableName : views ) {
				generateView( DBHandle, tableName );

				count++;
			}

			print( "" + count + " view objects generated." );
		}

		disconnect( DBHandle );
	}
	catch ( string e ) {
		print( "Exception: " + e );
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}
	catch {
		print( "Exception: caught unknown exception" );
	}
}



int connect() modify throws {
	int handle = mysql_init();
	handle = mysql_real_connect(handle, Host, Port, User, Password, Database);

	if ( !handle ) {
		throw "failed to connect to database " + Database;
	}

	return handle;
}

void disconnect(int handle) modify {
	mysql_close(handle);
}

void generateTable(int dbHandle, string name) modify {
	var generator = new Generator(dbHandle);
	var table = generator.generate(name);

	string tableData = LINEBREAK;
	tableData += "public object " + TABLE_PREFIX + toUpper(name) + TABLE_POSTFIX + " {" + LINEBREAK;
	foreach ( Pair<string, string> field : table ) {
		tableData += "	public " + field.second + " " + field.first + ";" + LINEBREAK;
	}
	tableData += "}" + LINEBREAK + LINEBREAK;

	var outFile = new System.IO.File(Database + "/Tables/" + toUpper(name) + ".os", System.IO.FileAccessMode.WriteOnly);
	outFile.write(tableData);
	outFile.close();
}

void generateView(int dbHandle, string name) modify {
	var generator = new Generator(dbHandle);
	var view = generator.generate(name);

	string viewData = LINEBREAK;
	viewData += "public object " + VIEW_PREFIX + toUpper(name) + VIEW_POSTFIX + " {" + LINEBREAK;
	foreach ( Pair<string, string> field : view ) {
		viewData += "	public " + field.second + " " + field.first + ";" + LINEBREAK;
	}
	viewData += "}" + LINEBREAK + LINEBREAK;

	var outFile = new System.IO.File(Database + "/Views/" + toUpper(name) + ".os", System.IO.FileAccessMode.WriteOnly);
	outFile.write(viewData);
	outFile.close();
}

void prepareFolders() modify {
	system("mkdir -p " + Database + "/Tables");
	system("mkdir -p " + Database + "/Views");
}

