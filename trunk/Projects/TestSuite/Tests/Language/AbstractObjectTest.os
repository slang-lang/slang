#!/usr/local/bin/oscript

public abstract object AbstractObject {
	public bool isAbstract() const;
}

public object ImplementedObject extends AbstractObject {
	public bool isAbstract() const {
		return false;
	}
}

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
	}

	private bool TestCase1() const {
		AbstractObject obj = new ImplementedObject();

		print("obj.isAbstract() = " + obj.isAbstract());

		assert( obj is Object );
		assert( obj is AbstractObject );
		assert( obj is ImplementedObject );
		assert( !obj.isAbstract() );

		return true;
	}
}

