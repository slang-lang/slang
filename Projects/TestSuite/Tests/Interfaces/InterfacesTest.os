#!/usr/local/bin/oscript

public namespace Tests
{
	public namespace Interfaces
	{
		public interface IWarehouse
		{
			public Number GetBox() const;
		}

		public object Warehouse implements public IWarehouse
		{
			public Number GetBox() const
			{
				// either this..
				return Number(1);
				// or that..
				//return 1;
			}
		}

		public object Main
		{
			public void Main(Number argc = 0, String argv = "")
			{
				test();
			}

			private void test()
			{
				Warehouse warehouse = new Warehouse();

				print("IWarehouse.GetBox() = " & warehouse.GetBox());

				delete warehouse;	// this is not necessary but perfectly valid
			}
		}
	}
}
