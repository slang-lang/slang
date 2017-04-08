#!/usr/local/bin/oscript

public void Main(int argv, string args) {
	writeln("getenv(\"QUERY_STRING\") = " + getenv("QUERY_STRING"));

	writeln("get(\"name\") = " + isSet("name"));
	writeln("get(\"city\") = " + isSet("city"));
	writeln("get(\"state\") = " + isSet("state"));
	writeln("get(\"sidekick\") = " + isSet("sidekick"));
}

