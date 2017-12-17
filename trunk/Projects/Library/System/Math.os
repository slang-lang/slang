
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public namespace Math {

	public double PI const = 3.14159265359d;

	public double power(double value) {
		return value * value;
	}

	public double power(double value, int exp) {
		double result = value;

		while ( exp > 1 ) {
			result *= value;
			exp -= 1;
		}

		return result;
	}

	public float power(float value) {
		return value * value;
	}

	public float power(float value, int exp) {
		float result = value;

		while ( exp > 1 ) {
			result *= value;
			exp -= 1;
		}

		return result;
	}

	public int power(int value) {
		return value * value;
	}

	public int power(int value, int exp) {
		int result = value;

		while ( exp > 1 ) {
			result *= value;
			exp -= 1;
		}

		return result;
	}

	public double sqr(double value) {
		return power(value, 2);
	}

	public float sqr(float value) {
		return power(value, 2);
	}

	public int sqr(int value) {
		return power(value, 2);
	}

}

