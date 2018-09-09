#!/usr/local/bin/oscript

public namespace Outer {

	public object SpacedObject { }

	public object OtherObject {
		private SpacedObject mObject;

		public void Constructor() {
			mObject = new SpacedObject();
		}

		public SpacedObject getObject() const {
			return mObject;
		}

		public void setObject(SpacedObject obj) modify {
			mObject = obj;
		}
	}

}


public void Main(int argc, string args) {
	Outer.OtherObject obj = new Outer.OtherObject();

	print(typeid(obj));
	print(typeid(obj.getObject()));

	obj.setObject(new Outer.SpacedObject());

	print(typeid(obj.getObject()));
}

