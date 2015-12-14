
public namespace System
{
	public object Console
	{
		public void write(string text) static
		{
			print(text);
		}

		public void writeln(string text) static
		{
			print(text & "\n");
		}
	}
}