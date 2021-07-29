
// Library imports
import System.Collections.IIterable;
import System.Collections.Map;

// Project imports
import Scanner;


public object TemplateLookup implements IIterable {
	public void fetchTemplates() modify {
		mTemplates = new Map<string, string>();

		process();
	}

	public Iterator getIterator() const {
		return mTemplates.getIterator();
	}

	private string parseValue( CharacterIterator it ) const {
		string c;
		string value;

		while ( it.hasNext() && ( c = it.next() ) != "\"" ) {
			value += c;
		}

		return value;
	}

	private void process() modify throws {
		var charIt = new Scanner( CONFIG_DIRECTORY + "Templates.txt" ).getIterator();

		while ( charIt.hasNext() ) {
			skipChars( charIt );

			var key = parseValue( charIt );

			skipChars( charIt );

			var value = parseValue( charIt );

			mTemplates.insert( key, value );
		}
	}

	private void skipChars( CharacterIterator it ) const {
		while ( it.hasNext() && it.next() != "\"" );
	}

	private Map<string, string> mTemplates;
}

