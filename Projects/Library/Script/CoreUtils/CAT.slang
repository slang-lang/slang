
// library imports

// project imports
import ShellCommand;


public object CAT extends ShellCommand implements ICollection, IIterable
{
	public void Constructor() {
		base.Constructor( "cat" );
	}
}

