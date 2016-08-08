#!/usr/local/bin/oscript

public namespace OutterSpace.InnerSpace.AnotherSpace {
	public object SpacedObject {
		private int mValue;

		public void SpacedObject(int value) {
			print("SpacedObject(" + value + ")");

			mValue = value;
		}
	}
}

public object Main {
	public void Main(int argc, string args) {
		OutterSpace.InnerSpace.AnotherSpace.SpacedObject obj1 = new OutterSpace.InnerSpace.AnotherSpace.SpacedObject(173);
	}
}

