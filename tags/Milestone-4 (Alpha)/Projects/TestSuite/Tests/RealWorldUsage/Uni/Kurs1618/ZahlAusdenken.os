#!/usr/local/bin/oscript

    public void Main(int argc, string args) {
        // default initialisierung unseres startwerts
	write("Startwert: ");
        int startzahl = int cin();

        // setze das ergebnis (vorläufig) auf den startwert
        int ergebnis = startzahl;

        if (ergebnis > 0) {
            // wenn wir bereits ein gültiges ergebnis haben inkrementierte es mit 2
            ergebnis = ergebnis + 2;
        }
        else {
            // ist unser ergebnis <= 0 invertiere es und inkrementiere anschließend mit 2
            ergebnis = ergebnis * (-1) + 2;
        }

        // solange das ergebnis größer 2 ist, dekrementiere es um 2
        while (ergebnis > 2) {
            ergebnis = ergebnis - 2;
        }

        int arbeiten = 4;
        // führe eine schleife 10 mal aus
        // oder
        // zähle von 2 bis 22 (mit einem inkrement von 2)
        for (int i = 2; i <= 20; i = i + 2) {
            arbeiten = arbeiten + startzahl;
        }

        // gib einen text, je nach dem aktuellen ergebnis aus
        switch (ergebnis) {
            case 0: {
                writeln("Das kann nicht sein!");
                break;
            }
            case 1: {
                writeln("Die urspruengliche Zahl war ungerade!");
                break;
            }
            case 2: {
                writeln("Die urspruengliche Zahl war gerade!");
                break;
            }
            default: {
                writeln("Fehler!");
                break;
            }
        }

        // erinnere den user an seine ursprünglich angegebene zahl
        writeln("startzahl = " + startzahl);
    }

