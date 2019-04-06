#!/usr/local/bin/oscript

public object CompareUnequalContent {
	public int mValue = 173;

	public bool operator==(int other) const {
		return mValue == other;
	}
}

public void Main(int argc, string args) {
	var value = new CompareUnequalContent();

	if ( value != 173 ) {
		print("1: Compare unequal operator");
	}
	if ( value !== 173 ) {
		print("2: Compare unequal content operator");
	}

	if ( value != new CompareUnequalContent() ) {
		print("3: Compare unequal operator");
	}
	if ( value !== new CompareUnequalContent() ) {
		print("4: Compare unequal content operator");
	}
}

