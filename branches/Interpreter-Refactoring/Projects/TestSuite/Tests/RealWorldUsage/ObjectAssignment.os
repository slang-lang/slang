#!/usr/local/bin/oscript

private object Vector2D {
	private int x;
	private int y;

	public void Vector2D(int x, int y) {
		print("Vector2D(" + x + ", " + y + ")");

		this.x = x;
		this.y = y;
	}

	public void ~Vector2D() {
		print("~Vector2D(" + x + ", " + y + ")");
	}

	public string ToString() const {
		return "Vector2D = { " + x + " / " + y + " }";
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

public object Main {
	public void Main(int argc, string args) {
		Vector2D v1 = new Vector2D(1, 1);
		print(v1.ToString());

		Vector2D v2 = new Vector2D(2, 2);
		print(v2.ToString());

		v1 = v2;
		print(v1.ToString());

		assert( v1 == v2 );
	}
}

