#!/usr/local/bin/oscript

import System.Collections.List;

private object IntList extends List<int> {
	public void sort(bool less[int a, int b]) {
		int tmp;

		for ( int value : this ) {
			if ( less(a, b) ) {
				swap(a, b);
			}
		}
	}

	private void swap(int left, int right) modify {
		int tmpLeft = at(left);
		int tmpRight = at(right);
		
	}
}

public void Main(int argc, string args) {
	var list = new IntList();

	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	list.sort( bool[int a, int b] => { return a < b; } );
}

