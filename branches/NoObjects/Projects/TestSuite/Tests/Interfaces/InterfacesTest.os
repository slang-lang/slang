
public namespace
{
	public interface IWarehouse
	{
		public Number GetBox() const;
	}

	public object Warehouse implements IWarehouse
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
		public void Main()
		{
			Warehouse w = new Warehouse();

			print("IWarehouse.GetBox() = " & w.GetBox());

			// this is not necessary but perfectly valid:
			delete w;
		}
	}
}
