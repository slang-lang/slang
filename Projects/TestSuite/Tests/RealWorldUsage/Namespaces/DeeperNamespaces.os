#!/usr/local/bin/slang

public namespace OutterSpace.InnerSpace.AnotherSpace {
	public object SpacedObject {
		private int mValue;

		public void Constructor(int value) {
			print("SpacedObject(" + value + ")");

			mValue = value;
		}
	}
}

public void Main(int argc, string args) {
	OutterSpace.InnerSpace.AnotherSpace.SpacedObject obj1 = new OutterSpace.InnerSpace.AnotherSpace.SpacedObject(173);
}

