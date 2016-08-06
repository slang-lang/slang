#!/usr/local/bin/oscript

import System.Math;

public object Main {
	private int MAXBURN const = 30;

	private float mCapsuleWeight = 14741.f; /*kg*/
	private int mFuel = 120; /*kg*/
	private float mGravity = 1.62f;	/*m/s2*/
	private float mHeight = 500.f; /*m*/
	private int mTimeStep = 10; /*s*/
	private float mVelocity = 0.f; /*m/s*/

	public void Main(int argc, string args) {
		printIntro();

		runGame();

		printOutro();
	}

	private void runGame() modify {
		float time = 0.f;

		while ( mHeight > 0.f ) {
			printStats();

			int burn = -1;
			while ( burn < 0 ) {
				cout("Booster: ");
				burn = Math.abs(int cin());
			}

			// only burn as much fuel as we have
			if ( burn > mFuel ) {
				burn = mFuel;
			}

			// our booster can only process MAXBURN units of fuel at a time
			if ( burn > MAXBURN ) {
				burn = MAXBURN;
			}

			/*
			distance = G * s^2 / 2 + v0 * t
			*/

			float distance = (mGravity * mTimeStep * mTimeStep / 2.f) + (mVelocity * mTimeStep - (float burn * mTimeStep * 1.f));
			mVelocity = distance / mTimeStep;

			mHeight = mHeight - distance;
			mFuel = mFuel - Math.abs(burn);

			time = time + mTimeStep;	// count time to touchdown

			//sleep(mTimeStep * 1000);	// really wait for (mTimeStep) seconds
		}

		writeln("ON THE MOON AFTER " + time + " SECONDS");
	}

	private void printIntro() {
		writeln("==============");
		writeln("|LUNAR LANDER|");
		writeln("==============");
		writeln();
		writeln("THIS IS A COMPUTER SIMULATION OF AN APOLLO LUNAR LANDING CAPSULE.");
		writeln();
		writeln("THE ON-BOARD COMPUTER HAS FAILED (IT WAS MADE BY XEROX) SO YOU ");
		writeln("HAVE TO LAND THE CAPSULE MANUALLY.");
		writeln("SET BURN RATE OF RETRO ROCKETS TO ANY VALUE BETWEEN 0 (FREE FALL)");
		writeln("AND " + MAXBURN + " (MAXIMUM BURN) POUNDS PER SECOND.");
		writeln("SET NEW BURN RATE EVERY 10 SECONDS.");
		writeln("CAPSULE WEIGHT " + mCapsuleWeight + " KG; FUEL WEIGHT " + mFuel + " KG.");
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
}

