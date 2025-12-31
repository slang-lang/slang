
// library imports

// project imports
import ShellCommand;


public object LS extends ShellCommand implements ICollection, IIterable
{
	public void Constructor() {
		base.Constructor( "ls" );
	}
}

