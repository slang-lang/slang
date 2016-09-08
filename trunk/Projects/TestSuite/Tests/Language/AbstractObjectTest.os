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
	public void Main(int argc, string args) {
		AbstractObject obj = new ImplementedObject();

		print("obj.isAbstract() = " + obj.isAbstract());

		assert( obj is Object );
		assert( obj is AbstractObject );
		assert( obj is ImplementedObject );
		assert( !obj.isAbstract() );
	}
}

