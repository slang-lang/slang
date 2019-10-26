
// Library imports

// Project imports
import IContext;


public stable interface ILogger {
	public IContext getContext() const;
	public string getKey() const;
	public int getKeyLength() const;

	public void debug(string message) modify;
	public void error(string message) modify;
	public void fatal(string message) modify;
	public void info(string message) modify;
	public void warning(string message) modify;
}

