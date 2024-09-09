#!/usr/local/bin/slang

private object OTmp {
	public int getInt() const {
		return 173;
	}
}

public void Main(int argc, string argv) {
	writeln("type cast madness: go!");

	OTmp tmp = new OTmp();

	writeln("tmp = " + tmp.getInt());
	writeln("value = " + (string getIntValue()));
	writeln("value = " + float getIntValue());
	writeln("value = " + (string (int (string float getIntValue()))));
	writeln("bla = " + double string float 1.7d);
}

private int getIntValue() const {
	return 1389;
}

