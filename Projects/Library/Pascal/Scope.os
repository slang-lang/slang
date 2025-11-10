
// library imports
import System.Collections.Stack;

// project imports
import SymbolTable;


public object Scope extends SymbolTable {
	public void Constructor(string name, Scope parent = null, bool allowBreakAndContinue = false) {
		base.Constructor(name, cast<SymbolTable>( parent ));

		mProperties = new Stack<ScopeProperty>();

		pushProperty(allowBreakAndContinue);
	}

	public void Destructor() {
		popProperty();
	}

	public bool isBreakAllowed() const {
		return mProperties.peek().AllowBreakAndContinue;
	}

	public bool isContinueAllowed() const {
		return mProperties.peek().AllowBreakAndContinue;
	}

	public void popProperty() modify {
		mProperties.pop();
	}

	public void pushProperty(bool allowBreakAndContinue) modify {
		mProperties.push( new ScopeProperty(allowBreakAndContinue) );
	}

	private Stack<ScopeProperty> mProperties;
}


public object ScopeProperty {
	public bool AllowBreakAndContinue const;

	public void Constructor(bool allowBreakAndContinue = false) {
		AllowBreakAndContinue = allowBreakAndContinue;
	}
}

