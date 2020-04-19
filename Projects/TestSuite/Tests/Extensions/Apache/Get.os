#!/usr/local/bin/slang

public void Main(int argv, string args) {
	writeln("getenv(\"QUERY_STRING\") = " + getenv("QUERY_STRING"));

	writeln("get(\"name\") = " + get("name"));
	writeln("get(\"city\") = " + get("city"));
	writeln("get(\"state\") = " + get("state"));
	writeln("get(\"sidekick\") = " + get("sidekick"));
}

