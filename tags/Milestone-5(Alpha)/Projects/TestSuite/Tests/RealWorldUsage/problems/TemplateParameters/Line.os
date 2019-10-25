
public object Line {
	public int mValue;

	public bool operator<(Line other) {
		return mValue < other.mValue;
	}
}

