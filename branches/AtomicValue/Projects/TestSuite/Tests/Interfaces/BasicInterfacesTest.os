#!/usr/local/bin/oscript

public interface IGetBox {
	public int GetBox() const;
}

public object Boxhouse implements IGetBox {
	public int GetBox() const {
		return 173;
	}
}

public interface IGetBoxType {
	public string GetBoxType(int boxId) const;
}

public object Warehouse
	extends Boxhouse
	implements IGetBoxType
{
//	public string GetBoxType(int boxId) const { return "bla"; }
}

public object Main {
	public void Main(int argc = 0, string argv = "") {
		assert( TestCase1() );
		assert( TestCase2() );
	}

	private bool TestCase1() {
		Boxhouse boxhouse = new Boxhouse();

		print("boxhouse.GetBox() = " + boxhouse.GetBox());

		delete boxhouse;	// this is not necessary but perfectly valid

		return true;
	}

	private bool TestCase2() {
		Warehouse warehouse = new Warehouse();

		print("warehouse.GetBox() = " + warehouse.GetBox());
		print("warehouse.GetBoxType(1389) = " + warehouse.GetBoxType(1389) );

		delete warehouse;	// this is not necessary but perfectly valid

		return false;
	}
}

