
// library imports

// project imports
import ShellCommand;


public object UPTIME extends ShellCommand implements ICollection, IIterable
{
	public void Constructor() {
		base.Constructor( "uptime" );
	}
}

