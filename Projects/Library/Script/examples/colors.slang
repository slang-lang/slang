#!/usr/bin/env slang

import libs.Console;


public void Main( int argc, string args )
{
	Console.Reset();
	Console.SetTextUnderline();
	Console.SetTextColor( Console.Color.Green );
	Console.Echo( "This is green text." );
	Console.SetTextColor( Console.Color.White );
	Console.Echo( "This is not green text." );
	Console.Reset();
}

