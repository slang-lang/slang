
// library imports

// project imports
import ShellCommand;


public object GREP extends ShellCommand implements ICollection, IIterable
{
	public void Constructor() {
		base.Constructor( "grep" );
	}
}

