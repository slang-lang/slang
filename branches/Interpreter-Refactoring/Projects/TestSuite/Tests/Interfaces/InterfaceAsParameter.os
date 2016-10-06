#!/usr/local/bin/oscript

import System.Exception;

//public object Box;	// forward declarations are not needed

public interface IWarehouse {
	public void insert(Box b ref);
	public bool isFull() const;
	public void takeOut();
}

public object Box {
	private int mId;

	public void Box(int id) {
		mId = id;
	}
}

public object Warehouse implements IWarehouse {
	private Box mBox;

	public void insert(Box box ref) modify throws {
		if ( mBox ) {
			throw new System.Exception("Warehouse is already full!");
		}

		mBox = box;
	}

	public bool isFull() const {
		return bool mBox;
	}

	public void takeOut() modify throws {
		if ( !mBox ) {
			throw new System.Exception("Warehouse is empty!");
		}

		mBox = null;
	}
}

public object Observer {
	private IWarehouse mWarehouse;

	public void Observer(IWarehouse wh ref) {
		mWarehouse = wh;
	}

	public bool isFull() const {
		return mWarehouse.isFull();
	}
}

public object Main {
	public void Main(int argc = 0, string args = "") {
		IWarehouse wh = new Warehouse();
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
		catch ( System.Exception e ) {
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
		catch ( System.Exception e ) {
			print(e.what());
		}
	}
}

