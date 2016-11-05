
public object BaseObjectImported {
	public void Constructor() {
		print("Constructor()");
	}

	public void Destructor() {
		print("Destructor()");
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

