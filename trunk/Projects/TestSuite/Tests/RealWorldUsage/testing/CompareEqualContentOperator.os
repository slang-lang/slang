#!/usr/local/bin/oscript

public object CompareEqualContent {
	public int mValue = 173;

	public bool operator==(int other) const {
		return mValue == other;
	}
}

public void Main(int argc, string args) {
	var value = new CompareEqualContent();

	if ( value == 173 ) {
		print("1: Compare equal operator");
	}
	if ( value === 173 ) {
		print("2: Compare equal content operator");
	}

	if ( value == new CompareEqualContent() ) {
		print("3: Compare equal operator");
	}
	if ( value === new CompareEqualContent() ) {
		print("4: Compare equal content operator");
	}
}

