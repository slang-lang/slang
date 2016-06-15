#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc, string argv) {
		int error = 0;
		int handle = mysql_init();
		int result_handle = 0;

		handle = mysql_real_connect(handle, "192.168.0.22", 0, "oscript", "oscript", "");
		if ( !handle ) {
			writeln("error while connecting to database!");
			return;
		}

		error = mysql_select_db(handle, "ts_parking");
		writeln("mysql_select_db(" + handle + "\"ts_parking\") = " + error);
		if ( error ) {
			writeln("error while selecting database: " + error);
			return;
		}

		mysql_close(handle);
	}
}

