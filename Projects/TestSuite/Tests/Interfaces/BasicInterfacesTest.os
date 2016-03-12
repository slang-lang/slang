#!/usr/local/bin/oscript

public namespace InterfacesTest
{
	public interface IWarehouse
	{
		public int GetBox() const;
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

			delete warehouse;	// this is not necessary but perfectly valid
		}
	}
}

