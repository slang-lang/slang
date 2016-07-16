#!/usr/local/bin/oscript

private namespace OutterSpace {
	private object OutterObject {
		private int mValue;

		public void OutterObject(int value) {
			mValue = value;
		}
	}

	private namespace InnerSpace {
		private object NestedObject {
			private OutterObject mValue;

			public void NestedObject(int value) {
				mValue = new OutterSpace.OutterObject(value);
			}
		}
	}
}

private namespace OutterSpace {
	private int mPublicVar;

	private object SecondOutterObject {
		public void SecondOutterObject(int value) {
			OutterSpace.mPublicVar = value;
		}
	}
}

public object Main {
	public void Main(int argc, string args) {
		assert( TestCase1() );
	}

	private bool TestCase1() const {
		OutterObject obj1 = new OutterSpace.OutterObject(1);
		print("obj1.mValue = " + obj1.mValue);

		NestedObject obj2 = new OutterSpace.InnerSpace.NestedObject(2);
		print("obj2.mValue.mValue = " + obj2.mValue.mValue);

		SecondOutterObject obj3 = new OutterSpace.SecondOutterObject(3);
		obj3 = new OutterSpace.SecondOutterObject(4);

		print("OutterSpace.mPublicVar = " + OutterSpace.mPublicVar);

		return true;
	}
}

