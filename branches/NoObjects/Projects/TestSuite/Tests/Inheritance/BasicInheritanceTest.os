
public namespace Inheritance
{
	public object Base
	{
		public String getBaseName() const
		{
			return "Base";
		}
	}

	public object Extended extends Base
	{
		public String getExtendedName() const
		{
			return "Extended";
		}
	}

	public object Main
	{
		public void Main()
		{
			Base base = new Base();
			Extended extended = new Extended();

			print("base.getBaseName = " & base.getBaseName());
			print("extended.getBaseName = " & extended.getBaseName());
			print("extended.getExtendedName = " & extended.getExtendedName());

			delete base;
			delete extended;
		}
	}
}
