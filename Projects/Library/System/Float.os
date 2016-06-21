
public namespace System {

	public object Float {
		private float mValue;

		public void Float(float value = 0f) {
			mValue = value;
		}
		public void Float(Float copy) {
			mValue = copy.mValue;
		}

		public void FromString(string value) modify {
			mValue = float value;
		}

		/*
		 * Returns a JSON-formatted string
		 */
		public string ToJsonString() const {
			return "{ " +
						"mValue: " + mValue + +
				" }";
		}

		public string ToString() const {
			return "Float: " + mValue;
		}

		public deprecated float Value() const {
			return mValue;
		}
		public deprecated void Value(float value) modify {
			mValue = value;
		}

		public bool operator!() const {
			return !mValue;
		}

		public bool operator==(float other) const {
			return mValue == other;
		}
		public bool operator==(Float other) const {
			return mValue == other.mValue;
		}

		public void operator=(float other) modify {
			mValue = other;
		}
		public void operator=(Float other) modify {
			mValue = other.mValue;
		}

		public float =operator(float other) const {
			return mValue;
		}

		public void operator+(float other) modify {
			mValue = mValue + other;
		}
		public void operator+(Float other) modify {
			mValue = mValue + other.mValue;
		}

		public void operator-(float other) modify {
			mValue = mValue - other;
		}
		public void operator-(Float other) modify {
			mValue = mValue - other.mValue;
		}

		public void operator*(float other) modify {
			mValue = mValue * other;
		}
		public void operator*(Float other) modify {
			mValue = mValue * other.mValue;
		}

		public void operator/(float other) modify {
			mValue = mValue / other;
		}
		public void operator/(Float other) modify {
			mValue = mValue / other.mValue;
		}
	}

}

