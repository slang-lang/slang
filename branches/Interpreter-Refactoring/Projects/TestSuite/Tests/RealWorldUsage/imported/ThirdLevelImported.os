
import DerivedObjectImported;

public object ThirdLevelImported extends DerivedObjectImported {
	public void ThirdLevelImported() {
		print("ThirdLevelImported()");
	}

	public void ~ThirdLevelImported() {
		print("~ThirdLevelImported()");
	}

	public string ToString() const {
		return "ThirdLevelImported extends " + base.ToString();
	}
}

