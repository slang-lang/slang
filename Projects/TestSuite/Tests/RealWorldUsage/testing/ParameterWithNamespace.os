#!/usr/local/bin/oscript

public namespace NS {
	public object SpacedObject {
		public int Value = 173;
	}
}

public void Main(int argc, string args) {
	var obj = new UnspacedObject();

	obj.Method(new NS.SpacedObject());
}

public object UnspacedObject {
	public void Method(NS.SpacedObject so) {
		print(so.Value);
	}
}

