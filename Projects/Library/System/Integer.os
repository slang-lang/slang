
public namespace System {

	public object Integer {
		private int mValue;

		public void Integer(int value = 0) {
			mValue = value;
		}
		public void Integer(Integer copy) {
			mValue = copy.mValue;
		}

		public void FromString(string value) modify {
			mValue = int value;
		}

		public string ToString() const {
			return string mValue;
		}

		public deprecated int Value() const {
			return mValue;
		}
		public deprecated void Value(int value) modify {
			mValue = value;
		}

		public bool operator!() const {
			return !mValue;
		}

		public bool operator==(int other) const {
			return mValue == other;
		}
		public bool operator==(Integer other) const {
			return mValue == other.mValue;
		}

		public void operator=(int other) modify {
			mValue = other;
		}
		public void operator=(Integer other) modify {
			mValue = other.mValue;
		}

		public void operator+(int other) modify {
			mValue = mValue + other;
		}
		public void operator+(Integer other) modify {
			mValue = mValue + other.mValue;
		}

		public void operator-(int other) modify {
			mValue = mValue - other;
		}
		public void operator-(Integer other) modify {
			mValue = mValue - other.mValue;
		}

		public void operator*(int other) modify {
			mValue = mValue * other;
		}
		public void operator*(Integer other) modify {
			mValue = mValue * other.mValue;
		}

		public void operator/(int other) modify {
			mValue = mValue / other;
		}
		public void operator/(Integer other) modify {
			mValue = mValue / other.mValue;
		}
	}

}

