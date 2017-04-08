#!/usr/local/bin/oscript

import System.Exception;

public object Box;	// forward declarations are not needed

public interface IWarehouse {
	public void insert(Box box ref);
	public bool isFull() const;
	public void takeOut();
}

public object Box {
	private int mId;

	public void Constructor(int id) {
		print("Box.Constructor(" + id + ")");

		mId = id;
	}
	public void Destructor() {
		print("Box.Destructor()");
	}
}

public object Warehouse implements IWarehouse {
	private Box mBox;

	public void Constructor() {
		print("Warehouse.Constructor()");
	}
	public void Destructor() {
		print("Warehouse.Destructor()");
	}

	public void insert(Box box ref) modify throws {
		if ( mBox ) {
			throw new Exception("Warehouse is already full!");
		}

		mBox = box;
	}

	public bool isFull() const {
		return bool mBox;
	}

	public void takeOut() modify throws {
		if ( !mBox ) {
			throw new Exception("Warehouse is empty!");
		}

		mBox = null;
	}
}

public object Observer {
	private IWarehouse mWarehouse;

	public void Constructor(IWarehouse wh ref) {
		print("Observer.Constructor(IWarehouse)");

		mWarehouse = wh;
	}
	public void Destructor() {
		print("Observer.Destructor()");
	}

	public bool isFull() const {
		return mWarehouse.isFull();
	}
}

public void Main(int argc = 0, string args = "") {
	IWarehouse wh = IWarehouse new Warehouse();
	Observer o = new Observer(wh);

	Box b = new Box(173);

	try {
		print("o.isFull() = " + o.isFull());
		wh.insert(b);
		print("o.isFull() = " + o.isFull());
		wh.takeOut();
		print("o.isFull() = " + o.isFull());
		wh.takeOut();
	}
	catch ( Exception e ) {
		print(e.what());
	}

	try {
		print("o.isFull() = " + o.isFull());
		wh.insert(b);
		print("o.isFull() = " + o.isFull());
		wh.insert(b);
		print("o.isFull() = " + o.isFull());
		wh.takeOut();
	}
	catch ( Exception e ) {
		print(e.what());
	}
}

