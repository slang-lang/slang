
// library imports

// project imports
import ShellCommand;


public object PS extends ShellCommand implements ICollection, IIterable
{
	public void Constructor() {
		base.Constructor( "ps" );
	}
}

