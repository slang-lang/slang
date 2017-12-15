
import BaseObject;

private object DerivedObject extends BaseObject {
	public void Constructor() {
		print("DerivedObject.Constructor()");
	}

	public void Destructor() {
		print("DerivedObject.Destructor()");
	}
	
	public string ToString() const {
		return "DerivedObject { mValue = " + mValue + "}";
	}
}

