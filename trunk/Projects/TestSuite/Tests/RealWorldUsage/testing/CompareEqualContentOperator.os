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
		print("Compare equal operator");
	}
	if ( value === 173 ) {
		print("Compare equal content operator");
	}
}

