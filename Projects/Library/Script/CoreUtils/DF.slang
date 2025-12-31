
// library imports

// project imports
import ShellCommand;


public object DF extends ShellCommand implements ICollection, IIterable
{
	public void Constructor() {
		base.Constructor( "df" );
	}
}


