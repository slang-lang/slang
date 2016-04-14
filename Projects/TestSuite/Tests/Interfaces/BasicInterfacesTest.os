#!/usr/local/bin/oscript

public namespace InterfacesTest
{
	public interface IWarehouse
	{
		public int GetBox() const;
		public string GetBoxType(int boxId) const;
	}

	public object Warehouse implements IWarehouse
	{
		public int GetBox() const
		{
			// either this..
			return int 1;
			// or that..
			//return 1;
		}

		//public string GetBoxType(int boxId) const { return "bla"; }
	}

	public object Main
	{
		public void Main(int argc = 0, string argv = "")
		{
			test();
		}

		private void test()
		{
			Warehouse warehouse = new Warehouse();

			print("IWarehouse.GetBox() = " + warehouse.GetBox());

			warehouse.GetBoxType(17);

			delete warehouse;	// this is not necessary but perfectly valid
		}
	}
}

