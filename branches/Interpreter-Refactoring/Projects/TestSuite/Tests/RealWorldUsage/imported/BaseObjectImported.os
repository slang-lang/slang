
public object BaseObjectImported {
	public void BaseObjectImported() {
		print("BaseObjectImported()");
	}

	public void ~BaseObjectImported() {
		print("~BaseObjectImported()");
	}

	public string ToString() const {
		return "BaseObjectImported";
	}

	protected bool isProtected() const {
		return true;
	}

	private bool isPrivate() const {
		return true;
	}
}

