
// library imports
import System.Collections.List;

// project imports
import Symbol;


public object SymbolTable {
	public int mLevel const;
	public string mName const;
	public SymbolTable mParent const;

	public void Constructor(int level, string name, SymbolTable parent = null) {
		mLevel = level;
		mName = name;
		mParent = parent;
		mSymbols = new List<Symbol>();

		//print("new SymbolTable(level: " + mLevel + ", name: \"" + mName + "\", parent: " + (mParent ? true : false) + ")");
	}

	public void Destructor() {
		//print("delete SymbolTable(level: " + mLevel + ", name: \"" + mName + "\", parent: " + (mParent ? true : false) + ")");
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

