
public namespace unstable InterfaceTest
{
	public interface stable IWarehouse
	{
		public stable Number GetBox() const;
	}

	public object deprecated Warehouse implements public IWarehouse
	{
		public deprecated Number GetBox() const
		{
			// either this..
			return Number(1);
			// or that..
			//return 1;
		}
	}

	public object unstable Main
	{
		public void unstable Main()
		{
			Warehouse w = new Warehouse();

			print("IWarehouse.GetBox() = " & w.GetBox());

			// this is not necessary but perfectly valid:
			delete w;
		}
	}
}
