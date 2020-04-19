#!/usr/local/bin/slang

public void Main(int argv, string args) {
	writeln("getenv(\"QUERY_STRING\") = " + getenv("QUERY_STRING"));

	writeln("post(\"name\") = " + post("name"));
	writeln("post(\"city\") = " + post("city"));
	writeln("post(\"state\") = " + post("state"));
	writeln("post(\"sidekick\") = " + post("sidekick"));
}

