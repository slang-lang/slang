#!/usr/bin/env slang

private namespace NS1 {

	public object TestObject {
		private int mValue;

		public void Constructor(int value) {
			mValue = value;

			print("mValue = " + mValue);
		}
	}

}

private namespace NS2 {

	public object TestObject {
		private string mValue;

		public void Constructor(string value) {
			mValue = value;

			print("mValue = " + mValue);
		}
	}

}

public void Main(int argc, string args) {
	NS1.TestObject ns1 = new NS1.TestObject(1);
	NS2.TestObject ns2 = new NS2.TestObject("bla");
}

