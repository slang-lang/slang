
// library imports
import System.Collections.List;

// project imports
import Symbol;


public object SymbolTable {
	public int mLevel const;
	public string mName const;
	public SymbolTable mParent const;

	public void Constructor(string name, SymbolTable parent = null) {
		mLevel = parent ? parent.mLevel + 1 : 0;
		mName = name;
		mParent = parent;
		mSymbols = new List<Symbol>();
	}

	public void Destructor() {
		// this is empty by intend
	}

	public Symbol at( int stackIndex ) const {
		return mSymbols.at( stackIndex );
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

	public int size() const {
		return mSymbols.size();
	}

	private List<Symbol> mSymbols;
}

