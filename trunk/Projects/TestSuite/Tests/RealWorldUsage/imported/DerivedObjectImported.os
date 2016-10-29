
import BaseObjectImported;

public object DerivedObjectImported extends BaseObjectImported {
	public void Constructor() {
		print("Constructor()");
	}

	public void Destructor() {
		print("Destructor()");
	}

	public string ToString() const {
		//isProtected();
		//isPrivate();
		return "DerivedObjectImported extends " + base.ToString();
	}
}

