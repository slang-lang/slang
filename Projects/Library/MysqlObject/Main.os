#!/usr/local/bin/oscript

// Library imports
import System.IO.File;

// Project imports
import DatatypeMapper;
import Generator;
import TableLookup;


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

void generateTable(int dbHandle, string tableName) const {
	var generator = new Generator(dbHandle);
	var table = generator.generate(tableName);

	string tableData = LINEBREAK;
	tableData += "public object " + tableName + " {" + LINEBREAK;
	foreach ( Pair<string, string> field : table ) {
		tableData += "	public " + field.second + " " + field.first + ";" + LINEBREAK;
	}
	tableData += "}" + LINEBREAK + LINEBREAK;

	var outFile = new System.IO.File("output/Table_" + tableName + ".os", System.IO.FileAccessMode.WriteOnly);
	outFile.write(tableData);
	outFile.close();
}

public void Main(int argc, string args) modify throws {
	try {
		int DBHandle = connect();

		var lookup = new TableLookup(DBHandle);
		var tables = lookup.getTables(Database);

		int count;
		foreach ( string tableName : tables ) {
			generateTable(DBHandle, tableName);

			count++;
		}

		print("" + count + " table objects generated.");

		disconnect(DBHandle);
	}
	catch ( string e ) {
		print("Exception: " + e);
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}
	catch {
		print("Exception: caught unknown exception");
	}
}

