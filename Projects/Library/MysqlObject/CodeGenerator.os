
// library imports
import System.String;

// project imports
import ConfigLoader;
import DatatypeMapper;
import Generator;
import Lookup;


public object CodeGenerator {
    public void Constructor() {
/*
        var configLoader = new ConfigLoader( Database + "/config.json" );
        configLoader.load();
        //configLoader.store();
*/        
    }

    public void process() modify throws {
        connect();

		var lookup = new Lookup( mDBHandle );

		// generate tables
		{
            var tables = lookup.getTables( Database );

			int count;
			foreach ( string tableName : tables ) {
				generateTable( mDBHandle, tableName );

				count++;
			}

			print( "" + count + " table objects generated." );
		}

		// generate views
		{
			var views = lookup.getViews( Database );

			int count;
			foreach ( string tableName : views ) {
				generateView( mDBHandle, tableName );

				count++;
			}

			print( "" + count + " view objects generated." );
        }

        disconnect();
    }

    private void connect() modify throws {
        mDBHandle = mysql_init();
        mDBHandle = mysql_real_connect(mDBHandle, Host, Port, User, Password, Database);
    
        if ( !mDBHandle ) {
            throw "failed to connect to database " + Database;
        }
    }

    private void disconnect() modify {
        mysql_close( mDBHandle );
    }

    private void generateTable(int dbHandle, string name) modify {
        var generator = new Generator(dbHandle);
        var table = generator.generate(name);
        var template = new String( readFile( "Table.txt") );
    
        string tableData = LINEBREAK;
        tableData += "public object " + TABLE_PREFIX + toUpper(name) + TABLE_POSTFIX + " {" + LINEBREAK;
        foreach ( Pair<string, string> field : table ) {
            tableData += "	public " + field.second + " " + field.first + ";" + LINEBREAK;
        }
        tableData += "}" + LINEBREAK + LINEBREAK;
    
        var outFile = new System.IO.File(Database + "/Tables/" + toUpper(name) + ".os", System.IO.FileAccessMode.WriteOnly);
        outFile.write(tableData);
        outFile.close();
    }

    private void generateView(int dbHandle, string name) modify {
        var generator = new Generator(dbHandle);
        var template = new String( readFile( "View.txt") );
        var view = generator.generate(name);
    
        string viewData = LINEBREAK;
        viewData += "public object " + VIEW_PREFIX + toUpper(name) + VIEW_POSTFIX + " {" + LINEBREAK;
        foreach ( Pair<string, string> field : view ) {
            viewData += "	public " + field.second + " " + field.first + ";" + LINEBREAK;
        }
        viewData += "}" + LINEBREAK + LINEBREAK;
    
        var outFile = new System.IO.File(Database + "/Views/" + toUpper(name) + ".os", System.IO.FileAccessMode.WriteOnly);
        outFile.write(viewData);
        outFile.close();
    }

    private void prepareFolders() modify {
        system("mkdir -p " + Output + /*"/" + Database +*/ "/Tables");
        system("mkdir -p " + Output + /*"/" + Database +*/ "/Views");
    }

    private string readFile(string filename) const {
        var file = new System.IO.File(filename, System.IO.FileAccessMode.ReadOnly);
    
        string text;
        while ( !file.isEOF() ) {
            text += file.readChar();
        }
    
        return text;
    }

    private int mDBHandle;
}
