#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	Summierer summierer = new Summierer();

	write("Startwert: ");
	int startWert = int cin();

	writeln("Ergebnis mit for-Schleife: " + summierer.forSumme(startWert));
	writeln("Ergebnis kleiner Gauss: " + summierer.kleinerGauss(startWert));
	writeln("Ergebnis rekursiv: " + summierer.rekursiveSumme(startWert));
}

public object Summierer {
	public int forSumme(int startWert) {
		int result = 0;

		for ( int i = 1; i <= startWert; i=i++ ) {
			result = result + i;
		}

		return result;
	}

	public int rekursiveSumme(int startWert) {
		if ( startWert > 0 ) {
			return startWert + rekursiveSumme(startWert - 1);
		}
		return 0;
	}

	public int kleinerGauss(int startWert) {
		return startWert * ( startWert + 1) / 2;
	}
}

