
public namespace Main
{
	public interface IWarehouse
	{
		public Number GetBox() const;
	}

	public object Main extends Base implements IWarehouse
	{
		public void Main()
		{
		}

		public Number GetBox() const
		{
			return Number(1);
		}
	}
}
