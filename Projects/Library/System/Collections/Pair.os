
public object Pair<F, S> {
	public F first;
	public S second;

	public void Constructor(F f, S s) {
		first = f;
		second = s;
	}

	public bool operator<(Pair<F, S> other ref) const {
		return first < other.first;
	}

	public bool operator==(Pair<F, S> other ref) const {
		return first == other.first;
	}

	public bool operator==(F other) const {
		return first == other;
	}

	public string =operator(string none) const {
		return "{\"" + first + "\":" + second + "}";
	}
}

