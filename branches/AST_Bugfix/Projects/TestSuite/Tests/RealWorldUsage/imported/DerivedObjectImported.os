
import BaseObjectImported;

public object DerivedObjectImported extends BaseObjectImported {
	public void Constructor() {
		print("DerivedObjectImported.Constructor()");
	}

	public void Destructor() {
		print("DerivedObjectImported.Destructor()");
	}

	public string ToString() const {
		return "DerivedObjectImported extends " + base.ToString();
	}
}

