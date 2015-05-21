public namespace
{
	public object Main
	{
		public void Main()
		{
			test_while(5);
		}

		public void test_while(Number maxCount = 7)
		{
			Number count = 0;
			while ( count < maxCount ) {
				count = count + 1;
				print("count = " & count);
			}
		}
	}
}