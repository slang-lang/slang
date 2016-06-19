
public namespace System {
public namespace Math {

	public float PI;// = 3.14159265359f;

	public double abs(double value) {
		if ( value >= 0.0d ) {
			return value;
		}

		return value * -1;
	}

	public float abs(float value) {
		if ( value >= 0.0f ) {
			return value;
		}

		return value * -1;
	}

	public int abs(int value) {
		if ( value >= 0 ) {
			return value;
		}

		return value * -1;
	}

	public double power(double value) {
		return value * value;
	}

	public float power(float value) {
		return value * value;
	}

	public int power(int value) {
		return value * value;
	}

	public int power(int value, int exp) {
		int result = value;

		while ( exp > 1 ) {
			result = result * value;
			exp = exp--;
		}

		return result;
	}

	public double sqr(double value) {
		return power(value);
	}

	public float sqr(float value) {
		return power(value);
	}

	public int sqr(int value) {
		return power(value);
	}

}
}

