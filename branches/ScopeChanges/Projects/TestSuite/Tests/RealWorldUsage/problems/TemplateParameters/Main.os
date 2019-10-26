#!/usr/local/bin/oscript

import System.Collections.List;
import System.Collections.Map;
import Interpreter;
import Line;


public void Main(int argc, string args) {
	//var interpreter = new Interpreter( new List<Line>() );
	var interpreter = new Interpreter();

	paramList( new List<Line>() );
	paramMap( new Map<int, Line>() );
}

private void paramList(List<Line> list = null) {
	print( "type: " + typeid(list) );
}

private void paramMap(Map<int, Line> map = null) {
	print( "type: " + typeid(map) );
}

