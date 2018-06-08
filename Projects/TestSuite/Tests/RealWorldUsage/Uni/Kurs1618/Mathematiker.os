#!/usr/local/bin/oscript

import System.Exception;

public void Main(int argc, string args) {
    try {
        try {
            int i = 7 % 5;
            if ( (i / i % 2) == 1 ) {
                throw new Exception();
            }
            writeln("Ich mag");
        }
        catch ( Exception e ) {
            writeln("Ich liebe");
            try {
                if ((7 % 6 / (7 % 6 % 2)) == 1) {
                    throw new Exception();
                }
                writeln("nichts mehr, als");
            }
            catch ( Exception u ) {
                writeln("es,");
            }
        }
        writeln("wenn");
        try {
            int i = 1;
            switch ( i ) {
                case 0: {
                    writeln("eine Formel");
			break;
                }
                case 1: {
                    writeln("ein Programm");
			throw new Exception();
                }
                default: {
                    throw new Exception();
                }
            }
        }
        catch ( ArithmeticException e ) {
            writeln("abbricht.");
        }
        catch ( Exception e ) {
            writeln("funktioniert.");
        }
        finally {
            int i = 2;
            switch ( i ) {
                case 1: {
                    writeln(";)");
			break;
                }
                default: {
                    throw new Exception();
                }
            }
        }
    }
    catch ( ArithmeticException e ) {
        writeln(":(");
    }
    catch ( Exception e ) {
        writeln(" ");
    }
}

