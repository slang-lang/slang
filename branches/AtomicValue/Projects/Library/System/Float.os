
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

		public string ToString() const {
			return string mValue;
		}

		public float Value() const {
			return mValue;
		}
		public void Value(float value) modify {
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

