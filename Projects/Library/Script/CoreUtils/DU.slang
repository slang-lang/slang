
// library imports

// project imports
import ShellCommand;


public object DU extends ShellCommand implements ICollection, IIterable
{
	public void Constructor() {
		base.Constructor( "du" );
	}
}


