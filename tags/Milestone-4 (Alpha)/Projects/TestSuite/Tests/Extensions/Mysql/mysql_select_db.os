#!/usr/local/bin/oscript

public void Main(int argc, string argv) modify {
	int error = 0;
	int handle = mysql_init();
	int result_handle = 0;

	handle = mysql_real_connect(handle, "192.168.0.30", 3306, "root", "admin", "");
	if ( !handle ) {
		print("error while connecting to database!");
		return;
	}

	error = mysql_select_db(handle, "test");
	print("mysql_select_db(" + handle + "\"test\") = " + error);
	if ( error ) {
		print("error while selecting database: " + error);
		return;
	}

	mysql_close(handle);
}
