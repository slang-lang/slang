
// Library imports

// Project imports
import IContext;

//public namespace LibLog {

public interface ILogger {
	public IContext getContext() const;
	public string getKey() const;

	public void debug(string message);
	public void error(string message);
	public void fatal(string message);
	public void info(string message);
	public void warning(string message);
}

//}

