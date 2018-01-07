#!/usr/local/bin/oscript

private object Vector2D {
	public int x;
	public int y;
	private string name;

	public void Constructor(int _x, int _y) {
		print("Constructor(" + _x + ", " + _y + ")");

		this.x = _x;
		this.y = _y;
		this.name = string _x + y;
	}

	public void Destructor() {
		print("Destructor(" + x + ", " + y + ")");
	}

	public string ToString() const {
		return "Vector2D = { name: \"" + name + "\", " + x + ", " + y + " }";
	}

	public void operator=(Vector2D other ref) modify {
		print("operator=()");

		x = other.x;
		y = other.y;
	}

	public bool operator==(Vector2D other ref) const {
		print("operator==()");

		return x == other.x && y == other.y;
	}
}

public void Main(int argc, string args) {
	Vector2D v1 = new Vector2D(1, 1);
	print(v1.ToString());

	Vector2D v2 = new Vector2D(2, 2);
	print(v2.ToString());

	v1 = v2;
	print(v1.ToString());
	print(v2.ToString());

	assert( v1 == v2 );
}

