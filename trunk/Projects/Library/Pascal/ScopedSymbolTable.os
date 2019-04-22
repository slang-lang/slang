
// library imports
import System.Collections.List;

// project imports
import Symbol;


public object ScopedSymbolTable {
	public int mLevel const;
	public string mName const;
	public ScopedSymbolTable mParent const;

	public void Constructor(int level, string name, ScopedSymbolTable parent = null) {
		mLevel = level;
		mName = name;
		mParent = parent;
		mSymbols = new List<Symbol>();

		//print("new ScopedSymbolTable(level: " + mLevel + ", name: \"" + mName + "\", parent: " + (mParent ? true : false) + ")");
	}

	public void Destructor() {
		//print("delete ScopedSymbolTable(level: " + mLevel + ", name: \"" + mName + "\", parent: " + (mParent ? true : false) + ")");
	}

	public void declare(Symbol symbol) modify throws {
		if ( mSymbols.contains(symbol) ) {
			throw new Exception("duplicate symbol '" + symbol.mName + "' declared");
		}

		mSymbols.push_back(symbol);
	}

	public Symbol lookup(string name, bool onlyCurrentScope = false) const {
		foreach ( Symbol sym : mSymbols ) {
			if ( sym == name ) {
				return sym;
			}
		}

		if ( mParent && !onlyCurrentScope ) {
			return mParent.lookup(name);
		}

		return Symbol null;
	}

	private List<Symbol> mSymbols;
}

