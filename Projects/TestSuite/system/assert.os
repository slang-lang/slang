
namespace std
{

	public void assertmsg(String message const, Bool condition const) static
	{
		if ( condition == false ) {
			print(message);

			assert(condition);
		}
	}

}
