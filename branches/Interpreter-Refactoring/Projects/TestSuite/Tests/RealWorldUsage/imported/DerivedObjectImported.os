
import BaseObjectImported;

public object DerivedObjectImported extends BaseObjectImported {
	public void DerivedObjectImported() {
		print("DerivedObjectImported()");
	}

	public void ~DerivedObjectImported() {
		print("~DerivedObjectImported()");
	}

	public string ToString() const {
		//isProtected();
		//isPrivate();
		return "DerivedObjectImported extends " + base.ToString();
	}
}

