#!/usr/local/bin/oscript

private object ListItem;

private object ListItem {
	private ListItem mNext;
	private int mValue;
}

public object Main {
	public void Main(int argc, string args) {
		ListItem item1 = new ListItem();
		item1.mNext = new ListItem();
		item1.mValue = 1;

		ListItem item2 = new ListItem();
		item2.mValue = 2;

		item1.mNext = item2;

		ListItem item3 = new ListItem();
		item3.mValue = 3;

		item2.mNext = item3;

		ListItem tmp = item1;
		print("tmp.mValue = " + tmp.mValue);
		tmp = tmp.mNext;
		print("tmp.mValue = " + tmp.mValue);
		tmp = tmp.mNext;
		print("tmp.mValue = " + tmp.mValue);
	}
}

