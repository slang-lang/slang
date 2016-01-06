#!/usr/local/bin/oscript

public namespace Tests
{
	public namespace Interfaces
	{
		public interface IWarehouse
		{
			public number GetBox() const;
		}

		public object Warehouse implements public IWarehouse
		{
			public number GetBox() const
			{
				// either this..
				return number(1);
				// or that..
				//return 1;
			}
		}

		public object Main
		{
			public void Main(number argc = 0, string argv = "")
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
