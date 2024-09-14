#!/usr/local/bin/slang

public object CompareUnequalContent {
	public int mValue = 173;

	public bool operator==(int other) const {
		return mValue == other;
	}

	public bool operator==(CompareUnequalContent other const) const {
		return mValue == other.mValue;
	}
}

public void Main(int argc, string args) {
	var value = new CompareUnequalContent();
	value.mValue = 174;

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

