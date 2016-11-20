#!/usr/local/bin/oscript

private namespace OutterSpace {
	public object OutterObject {
		public int mValue;

		public void Constructor(int value) {
			mValue = value;
		}
	}

	public namespace InnerSpace {
		public object NestedObject {
			public OutterSpace.OutterObject mValue;

			public void Constructor(int value) {
				mValue = new OutterSpace.OutterObject(value);
			}
		}
	}
}

private namespace OutterSpace {
	public int mPublicVar;

	public object SecondOutterObject {
		public void Constructor(int value) {
			OutterSpace.mPublicVar = value;
		}
	}
}

public void Main(int argc, string args) {
	assert( TestCase1() );
}

private bool TestCase1() const {
	OutterSpace.OutterObject obj1 = new OutterSpace.OutterObject(1);
	print("obj1.mValue = " + obj1.mValue);

	OutterSpace.InnerSpace.NestedObject obj2 = new OutterSpace.InnerSpace.NestedObject(2);
	print("obj2.mValue.mValue = " + obj2.mValue.mValue);


	print("OutterSpace.mPublicVar = " + OutterSpace.mPublicVar);

	OutterSpace.SecondOutterObject obj3 = new OutterSpace.SecondOutterObject(3);

	print("OutterSpace.mPublicVar = " + OutterSpace.mPublicVar);

	obj3 = new OutterSpace.SecondOutterObject(4);

	print("OutterSpace.mPublicVar = " + OutterSpace.mPublicVar);

	return true;
}

