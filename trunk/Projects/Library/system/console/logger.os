
object Logger
{
	protected void debug(string text)
	{
		print("[DEBUG] " & text);
	}

	protected void error(string text)
	{
		print("[ERROR] " & text);
	}

	protected void warn(string text)
	{
		print("[WARN ] " & text);
	}
}
