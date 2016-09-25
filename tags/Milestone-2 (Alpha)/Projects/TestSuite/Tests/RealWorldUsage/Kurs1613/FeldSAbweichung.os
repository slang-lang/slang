#!/usr/local/bin/oscript

import System.Collections.List;
import System.Math;

private int FELDGROESSE const = 10;

// Berechnet die Standardabweichung der Werte im Feld inFeld
public void Main(int argc, string args) {
	// Mittelwert berechnen
	float Mittelwert = 0.f;
	//float inFeld[];
	System.List inFeld = new System.List();

	int idx;

	for ( idx = 0; idx < FELDGROESSE; idx = idx++ ) {
		int value = int cin();
		inFeld.push_back(Object value);
	}

	for ( idx = 0; idx < FELDGROESSE; idx = idx++ ) {
		Mittelwert = Mittelwert + inFeld.at(idx);
	}
	Mittelwert = Mittelwert / FELDGROESSE;

	// Standardabweichung berechnen
	float SAbweichung = 0.f;

	for ( idx = 0; idx < FELDGROESSE; idx = idx++ ) {
		SAbweichung = SAbweichung + Math.sqr(int inFeld.at(idx) - Mittelwert);
	}
	SAbweichung = SAbweichung / FELDGROESSE;

	writeln("FeldSAbweichung = " + sqrt(SAbweichung));
}

