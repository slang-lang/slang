
// Library imports
import libJsonBuilder.StyledBuilder;
import System.Collections.Set;
import System.IO.File;
import System.StringIterator;

// Project imports
import Consts;
import DatabaseConnection;
import Module;


private object Indexer {
	private Set<Module> mModules;
	private string mPath;

	public void Constructor(string path) {
		mModules = new Set<Module>();
		mPath = path;
	}

	public void buildIndex() modify {
		print("Building index from module information...");

		var command = "find " + mPath + "/modules -name \\*.json";
		var fileIt = new StringIterator(system(command), LINEBREAK);

		while ( fileIt.hasNext() ) {
			var curFile = new String(fileIt.next());

			if ( !cast<string>( curFile ) ) {
				continue;
			}

			int idx = -1;
			int idx2;
			while ( (idx2 = curFile.IndexOf(PATH_SEPARATOR, idx + 1)) != -1 ) {		// find last / character position
				idx = idx2;
			}

			curFile = curFile.SubString(idx + 1, curFile.Length());			// remove prefix
			curFile = curFile.SubString(0, curFile.Length() - 5);			// remove file extension

			idx = -1;
			while ( (idx2 = curFile.IndexOf(VERSION_SEPARATOR, idx + 1)) != -1 ) {		// find last _ character position
				idx = idx2;
			}

			var module = new Module(curFile.SubString(0, idx), curFile.SubString(idx + 1));
			if ( !module.isValid() ) {
				continue;
			}

			if ( (idx = mModules.indexOf(module)) != -1 ) {
				var other = mModules.at(idx);
				//print("found already existing module at index " + idx);

				if ( other < module ) {
					//print("erasing older module " + other.toString());
					mModules.erase(idx);
				}
				else {
					//print("inserting older module " + module.toString());
					continue;
				}
			}

			mModules.insert(module);
		}
	}

	public Set<Module> provideIndex() const {
		return mModules;
	}

	public void storeIndexFile() const {
		print("Storing index to file...");

		var builder = new Json.StyledBuilder();

		builder.beginArray("modules");
		foreach ( Module m : mModules ) {
			builder.beginObject();
			builder.addElement("name", m.name);
			builder.addElement("version", cast<string>( m.version) );
			builder.addElement("description", m.description);
			builder.endObject();
		}
		builder.endArray();

		var file = new System.IO.File(mPath + "/" + INDEX, "wt");
		file.write(builder.getString());
		file.close();
	}

	public void storeDatabase() const throws {
		print("Storing index to database...");

		try {
			DB.connect();

			int error = mysql_query(DB.mHandle, "BEGIN");
			if ( error ) {
				print("Transaction start failed!");
				throw mysql_error(DB.mHandle);
			}

			string query = "INSERT INTO modules (name, version, description, added) VALUES ";
			string values;

			foreach ( Module m : mModules ) {
				if ( values ) {
					values += ", ";
				}

				values += "( '" + m.name + "', '" + cast<string>( m.version ) + "', '" + m.description + "', NOW() )";
			}
			values += " ON DUPLICATE KEY UPDATE version = VALUES(version), last_update = NOW()";

			error = mysql_query(DB.mHandle, query + values);
			if ( error ) {
				print("Inserting values failed!");
				throw mysql_error(DB.mHandle);
			}

			error = mysql_query(DB.mHandle, "COMMIT");
			if ( error ) {
				print("Transaction commit failed!");
				throw mysql_error(DB.mHandle);
			}
		}
		catch ( string e ) {
			print("Exception: " + e);

			int error = mysql_query(DB.mHandle, "ROLLBACK");
			if ( error ) {
				print("Transaction rollback failed!");
				print(mysql_error(DB.mHandle));
			}
		}
		finally {
			DB.disconnect();
		}
	}
}

