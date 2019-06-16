#!/usr/local/bin/oscript

	public void Main(int argc, string argv) {
		int result;
		int result_handle;

		int handle = mysql_init();
		writeln("mysq_init() = " + handle);

		writeln("mysql_real_connect()");
		mysql_real_connect(handle, "127.0.0.1", 3306, "root", "", "test_objectivescript");

		string query = "SELECT * FROM parking_zones";

		result = mysql_query(handle, query);
		writeln("mysql_query(" + handle + ", \"" + query + "\") = " + result);

		if ( result != 0 ) {
			writeln("mysql_error(" + handle + ") = " + mysql_error(handle));
			writeln("failed.");
			return;
		}

		result_handle = mysql_store_result(handle);
		writeln("mysql_store_result(" + handle + ") = " + result_handle);

		int numRows = mysql_num_rows(result_handle);
		writeln("mysql_num_rows(" + result_handle + ") = " + numRows);

		int numFields = mysql_num_fields(result_handle);
		writeln("mysql_num_fields(" + result_handle + ") = " + numFields);

		bool printHeader = true;
		while ( mysql_next_row(result_handle) ) {
			string fields;
			string values;

			for ( int fieldId = 0; fieldId < numFields; fieldId = fieldId + 1) {
				fields = fields + " | " +  mysql_get_field_name(result_handle, fieldId);
				values = values + " | " +  mysql_get_field_value(result_handle, fieldId);
			}

			if ( printHeader ) {
				printHeader = false;
				writeln(fields);
			}
			writeln(values);
		}

		mysql_close(handle);
		writeln("mysql_close(" + handle + ")");

		writeln("done");
	}

