
public namespace System {
	public object Double {
		private double mValue;

		public void Double(double value = 0d) {
			mValue = value;
		}
		public void Double(Double copy) {
			mValue = copy.mValue;
		}

		public void FromString(string value) modify {
			mValue = double value;
		}

		public string ToString() const {
			return string mValue;
		}

		public deprecated double Value() const {
			return mValue;
		}
		public deprecated void Value(double value) modify {
			mValue = value;
		}

		public bool operator!() const {
			return !mValue;
		}

		public bool operator==(double other) const {
			return mValue == other;
		}
		public bool operator==(Double other) const {
			return mValue == other.mValue;
		}

		public void operator=(double other) modify {
			mValue = other;
		}
		public void operator=(Double other) modify {
			mValue = other.mValue;
		}

		public void operator+(double other) modify {
			mValue = mValue + other;
		}
		public void operator+(Double other) modify {
			mValue = mValue + other.mValue;
		}

		public void operator-(double other) modify {
			mValue = mValue - other;
		}
		public void operator-(Double other) modify {
			mValue = mValue - other.mValue;
		}

		public void operator*(double other) modify {
			mValue = mValue * other;
		}
		public void operator*(Double other) modify {
			mValue = mValue * other.mValue;
		}

		public void operator/(double other) modify {
			mValue = mValue / other;
		}
		public void operator/(Double other) modify {
			mValue = mValue / other.mValue;
		}
	}
}

