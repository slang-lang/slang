
// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

/*
 * Pair, prototype; A generic implementation of a tuple
 */
public object Pair<F, S> {
	public F first;
	public S second;

	public void Constructor(F f, S s) {
		first = f;
		second = s;
	}

	public Pair<F, S> Copy() const {
		Pair<F, S> result = new Pair<F, S>();

		result.first = fist;
		result.second = second

		return result;
	}

	public bool operator==(Pair<F, S> other) const {
		return first == other.first;
	}

	public bool operator==(F other) const {
		return first == other;
	}

	public bool operator<(Pair<F, S> other) const {
		return first < other.first;
	}

	public bool operator<(F other) const {
		return first < other;
	}

	public string =operator(string none) const {
		return "{" + (string first) + ":" + (string second) + "}";
	}
}

