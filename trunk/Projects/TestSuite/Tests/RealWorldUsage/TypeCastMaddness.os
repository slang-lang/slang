#!/usr/local/bin/oscript

private object OTmp {
	public int getInt() const {
		return 173;
	}
}

public object Main {
	public void Main(int argc, string argv) {
		writeln("type cast madness: go!");

		OTmp tmp;

		writeln("tmp = " + tmp.getInt());
		writeln("value = " + (string getIntValue()));
		writeln("value = " + float getIntValue());
		writeln("value = " + (string (int (string float getIntValue()))));
		writeln("bla = " + double string float number 1.7d);
	}

	public void ~Main() {
		writeln("yippi!");
	}

	private int getIntValue() const {
		return 1389;
	}
}

