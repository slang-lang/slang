#!/usr/local/bin/oscript

import Mysql.All;

private Mysql.Connection mConnection;

public void Main(int argc, string args) {
	Startup();

	UI_AddCountry();
	UI_ShowCountries();
}

private void Startup() modify throws {
	mConnection = new Mysql.Connection("192.168.0.20", 0, "oscript", "oscript", "ts_parking");
	if ( !mConnection.isOpen() ) {
		writeln("error while connecting to database!");
		throw new System.Exception("error while connecting to database!");
	}
}

private void UI_AddCountry() {
	writeln("<p>");
	writeln("Name: <input type='text' name='country' />");
	writeln("Shortcut: <input type='text' name='country_shortcut' size=2 />");
	writeln("<input type='button' value='Add Country' onclick='mPlugin.AddCountry();' />");
	writeln("</p>");
}

private void UI_ShowCountries() modify {
	Mysql.Result result = mConnection.query("SELECT id, name, shortcut FROM parking_countries ORDER BY name ASC");
	if ( !result ) {
		writeln("query failed!");
		return;
	}

	writeln("<table>");

	while ( result.hasNext() ) {
		result.next();

		UI_ShowCountry(result);
	}

	writeln("</table>");

	delete result;
}

private void UI_ShowCountry(Mysql.Result result) {
	Mysql.Entry name = result.getField("name");
	Mysql.Entry shortcut = result.getField("shortcut");

	writeln("<tr>");
	writeln("<td>" + name.value() + "</td><td>" + shortcut.value() + "</td>");
	writeln("</tr>");
}

