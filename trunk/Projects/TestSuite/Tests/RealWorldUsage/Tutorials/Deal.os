#!/usr/local/bin/oscript

import System.Collections.List;
import System.Collections.Stack;
import System.Collections.Vector;
import System.String;

private Vector deck;
private Stack rank;
private List suit;

public void Main(int argc, string args) {
	try {

	cout("numHands = ");
	int numHands = int cin();

	cout("cardsPerHand = ");
	int cardsPerHand = int cin();

	suit = new List();
	suit.push_back(Object new String("spades"));
	suit.push_back(Object new String("hearts"));
	suit.push_back(Object new String("diamonds"));
	suit.push_back(Object new String("clubs"));

	rank = new Stack();
	rank.push(Object new String("ace"));
	rank.push(Object new String("2"));
	rank.push(Object new String("3"));
	rank.push(Object new String("4"));
	rank.push(Object new String("5"));
	rank.push(Object new String("6"));
	rank.push(Object new String("7"));
	rank.push(Object new String("8"));
	rank.push(Object new String("9"));
	rank.push(Object new String("10"));
	rank.push(Object new String("jack"));
	rank.push(Object new String("queen"));
	rank.push(Object new String("king"));

	deck = new List();
	foreach ( String s : suit ) {
		foreach ( String r : rank ) {
			int key = rand() % (deck.size() + 1);
			print("key = " + key);

			deck.insert(int key, Object new String("" + r + " of " + s));
		}
	}

/*
	foreach ( String d : deck ) {
		print(string d);
	}
*/

	assert( numHands );
	assert( cardsPerHand );

	if ( numHands * cardsPerHand > deck.size() ) {
		print("Not enough cards.");
		return;
	}

	List hand = dealHand(cardsPerHand);
	foreach ( String s : hand ) {
		print(string s);
	}

	}
	catch ( string e ) {
		print("e = " + e);
	}
}

private List dealHand(int n) {
	List hand = new List();

	for ( int i = 0; i < n; i = i++ ) {
		string s = deck.at(i);

		hand.push_back(Object new String(s));
	}

	return hand;
}

