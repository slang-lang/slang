#!/usr/local/bin/oscript

private namespace OutterSpace {
	private namespace InnerSpace {
		public object InnerObject {
			private string mStringValue;

			public void InnerObject(string value) {
				print("InnerObject(" + value + ")");

				mStringValue = value;
			}
		}
	}

	public object OutterObject {
		private InnerSpace.InnerObject mInnerObject;
		private int mIntValue;

		public void OutterObject(int value) {
			print("OutterObject(" + value + ")");

			mIntValue = value;

			InnerSpace.InnerObject inner = new InnerSpace.InnerObject(string value * 2);
			mInnerObject = inner;
		}

		public InnerSpace.InnerObject getInnerObject() const {
			return mInnerObject;
		}
	}
}

public object Main {
	public void Main(int argc, string args) {
		assert( TestCase1() );
	}

	private bool TestCase1() {
		print("TestCase 1: Unqualified object instantiation");

		OutterSpace.OutterObject obj = new OutterSpace.OutterObject(173);

		return obj;
	}
}
