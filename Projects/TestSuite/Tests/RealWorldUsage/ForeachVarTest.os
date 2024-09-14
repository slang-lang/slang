#!/usr/local/bin/slang

import System.Collections.List;
import System.String;
import System.StringIterator;

public List<String> getList() const {
	List<String> list = new List<String>();
	list.push_back(new String("1"));
	list.push_back(new String("2"));
	list.push_back(new String("3"));

	return list;
}

public void Main(int argc, string args) {
        foreach ( var p : new String(args) ) {
                print("p = " + p);
        }

        foreach ( var s : String("1 2 3") ) {
                print("s = " + s);
        }

	foreach ( var i : getList() ) {
		print("i = " + cast<string>(i));
	}
}

