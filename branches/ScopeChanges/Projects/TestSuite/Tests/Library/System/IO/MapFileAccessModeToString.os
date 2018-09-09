#!/usr/local/bin/oscript

// NOTE: before using this System.IO.MapFileAccessModeToString has to be made public

import System.IO.File;

public void Main(int argc, string args) {
	try {
		print( System.IO.MapFileAccessModeToString(System.IO.FileAccessMode.ReadWrite) );
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}
}

