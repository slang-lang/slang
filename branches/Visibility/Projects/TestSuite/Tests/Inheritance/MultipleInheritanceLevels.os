#!/usr/local/bin/oscript

private object Level1 {
	private int mLevel1;

	public void Constructor() {
		mLevel1 = 1;

		print("Level1 constructor: " + mLevel1);
	}

	public void Destructor() {
		print("Level1 destructor: " + mLevel1);
	}
}

private object Level2 extends Level1 {
	private int mLevel2;

	public void Constructor() {
		base.Constructor();

		mLevel2 = 2;

		print("Level2 constructor: " + mLevel1 + " " + mLevel2);
	}

	public void Destructor() {
		print("Level2 destructor: " + mLevel1 + " " + mLevel2);
	}
}

private object Level3 extends Level2 {
	private int mLevel3;

	public void Constructor() {
		base.Constructor();

		mLevel3 = 3;

		print("Level3 constructor: " + mLevel1 + " " + mLevel2 + " " + mLevel3);
	}

	public void Destructor() {
		print("Level3 destructor: " + mLevel1 + " " + mLevel2 + " " + mLevel3);
	}
}

private object Level4 extends Level3 {
	private int mLevel4;

	public void Constructor() {
		base.Constructor();

		mLevel4 = 4;

		print("Level4 constructor: " + mLevel1 + " " + mLevel2 + " " + mLevel3 + " " + mLevel4);
	}

	public void Destructor() {
		print("Level4 destructor: " + mLevel1 + " " + mLevel2 + " " + mLevel3 + " " + mLevel4);
	}
}

private object Level4Replica replicates Level4;

public void Main(int argc, string argv) {
	Level4Replica replica = new Level4Replica();
	print(replica.mLevel1);
	print(replica.mLevel2);
	print(replica.mLevel3);
	print(replica.mLevel4);
}

