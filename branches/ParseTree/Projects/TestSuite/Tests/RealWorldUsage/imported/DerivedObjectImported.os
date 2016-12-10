
import BaseObjectImported;

public object DerivedObjectImported extends BaseObjectImported {
	public void Constructor() {
		print("Constructor()");
	}

	public void Destructor() {
		print("Destructor()");
	}

	public string ToString() const {
		return "DerivedObjectImported extends " + base.ToString();
	}
}

