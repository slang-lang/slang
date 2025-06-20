#!/usr/bin/env slang

import System.Collections.List;
import System.Math;
import System.Integer;

private int FELDGROESSE const = 5;

// Berechnet die Standardabweichung der Werte im Feld inFeld
public void Main(int argc, string args) {
	print("Berechnet den Mittelwert von 5 Zahlen:");

	// Mittelwert berechnen
	float Mittelwert = 0.f;
	List<int> inFeld = new List<int>();

	int idx;
	for ( idx = 0; idx < FELDGROESSE; idx = idx++ ) {
		inFeld.push_back(int cin());
	}

	for ( idx = 0; idx < FELDGROESSE; idx = idx++ ) {
		Mittelwert = Mittelwert + int inFeld.at(idx);
	}
	Mittelwert = Mittelwert / FELDGROESSE;

	// Standardabweichung berechnen
	float SAbweichung = 0.f;

	for ( idx = 0; idx < FELDGROESSE; idx = idx++ ) {
		SAbweichung = SAbweichung + Math.sqr((int inFeld.at(idx)) - Mittelwert);
	}
	SAbweichung = SAbweichung / FELDGROESSE;

	writeln("FeldSAbweichung = " + sqrt(SAbweichung));
}

