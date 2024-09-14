#!/usr/local/bin/slang

import System.Math;

private float CAPSULE_WEIGHT const = 14741.f; /*kg*/
private float MAXBURN const = 30.f;

private float mFuel = 120.f; /*kg*/
private float mGravity = 1.62f;	/*m/s2*/
private float mHeight = 500.f; /*m*/
private int mTimeStep = 10; /*s*/
private float mVelocity = 0.f; /*m/s*/

public void Main(int argc, string args) modify {
	printIntro();

	runGame();

	printOutro();
}

private void runGame() modify {
	float time = 0.f;

	while ( mHeight > 0.f ) {
		printStats();

		int percent = -1;
		while ( percent < 0 || percent > 100 ) {
			cout("Booster (%): ");
			percent = abs(int cin());
		}

		float burn = ((float percent) / 100.f) * MAXBURN;

		// only burn as much fuel as we have
		if ( burn > mFuel ) {
			burn = mFuel;
		}

		/*
		distance = G * s^2 / 2 + v0 * t
		*/

		float decceleration = burn / 10.f;
		float acceleration = mGravity - decceleration;
		float distance = (acceleration * mTimeStep * mTimeStep * 0.5f) + mVelocity * mTimeStep;

		mVelocity = distance / mTimeStep;
		mHeight = mHeight - distance;
		mFuel = mFuel - abs(burn);

		time = time + mTimeStep;	// count time to touchdown

		//sleep(mTimeStep * 1000);	// really wait for (mTimeStep) seconds
	}

	writeln("ON THE MOON AFTER " + time + " SECONDS");
}

private void printIntro() {
	writeln();
	writeln("==============");
	writeln("*LUNAR LANDER*");
	writeln("==============");
	writeln();
	writeln("THIS IS A COMPUTER SIMULATION OF AN APOLLO LUNAR LANDING CAPSULE.");
	writeln();
	writeln("THE ON-BOARD COMPUTER HAS FAILED (IT WAS MADE BY XEROX) SO YOU ");
	writeln("HAVE TO LAND THE CAPSULE MANUALLY.");
	writeln("SET BURN RATE OF RETRO ROCKETS TO ANY VALUE BETWEEN 0 (FREE FALL)");
	writeln("AND " + MAXBURN + " (MAXIMUM BURN) POUNDS PER SECOND.");
	writeln("SET NEW BURN RATE EVERY 10 SECONDS.");
	writeln("CAPSULE WEIGHT " + CAPSULE_WEIGHT + " KG; FUEL WEIGHT " + mFuel + " KG.");
	writeln("GOOD LUCK");
	writeln();
}

private void printOutro() {
	if ( mVelocity <= 1.2f ) {
		writeln("PERFECT LANDING, GOOD WORK!");
	}
	else if ( mVelocity < 10.f ) {
		writeln("GOOD LANDING (COULD BE BETTER)");
	}
	else {
		writeln("SORRY THERE ARE NO SURVIVORS. YOU BLOW IT!");
		writeln("IN FACT, YOU BLASTED A NEW LUNAR CRATER " + mVelocity * 0.227f + " METERS DEEP!");
	}
}

private void printStats() {
	writeln("Height: " + mHeight / 1000.f + "km, Velocity: " + mVelocity * 3.6f + "km/h, Fuel: " + mFuel + "kg, Gravity: " + mGravity + "m/s2");
}

