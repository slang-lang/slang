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

		float time = 0.f;

		while ( mHeight > 0.f ) {
			printStats();

			int burn = -1;
			while ( burn < 0 ) {
				burn = int cin();
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
			distance = mGravity * mTimeStep * mTimeStep / 2.f + mVelocity * mTimeStep
*/

			float distance = (mGravity * mTimeStep * mTimeStep / 2.f) + (mVelocity * mTimeStep - (float burn * mTimeStep * 1.f));
			mVelocity = distance / mTimeStep;

			mHeight = mHeight - distance;
			mFuel = mFuel - Math.abs(burn);

			time = time + mTimeStep;

			//sleep(mTimeStep * 1000);
		}

		writeln("ON THE MOON AFTER " + time + " SECONDS");

		printOutro();
	}

	private void printIntro() {
		writeln("LUNAR LANDER v0.0.1");
		writeln("THIS IS A COMPUTER SIMULATION OF AN APOLLO");
		writeln("LUNAR LANDING CAPSULE.");
		writeln();
		writeln("THE ON-BOARD COMPUTER HAS FAILED (IT WAS MADE");
		writeln("BY XEROX) SO YOU HAVE TO LAND THE CAPSULE MANUALLY.");
		writeln("SET BURN RATE OF RETRO ROCKETS TO ANY VALUE BETWEEN");
		writeln("0 (FREE FALL) AND 200 (MAXIMUM BURN) POUNDS PER SECOND.");
		writeln("SET NEW BURN RATE EVERY 10 SECONDS.");
		writeln("CAPSULE WEIGHT " + mCapsuleWeight + " KG; FUEL WEIGHT " + mFuel + " KG.");
		writeln("GOOD LUCK");
	}

	private void printOutro() {
		if ( mVelocity <= 1.2f ) {
			writeln("PERFECT LANDING, GOOD WORK!");
		}
		else if ( mVelocity < 10.f ) {
			writeln("GOOD LANDING (COULD BE BETTER)");
		}
		else {
			writeln("SORRY THERE NERE NO SURVIVORS. YOU BLOW IT!");
			writeln("IN FACT, YOU BLASTED A NEW LUNAR CRATER " + mVelocity * 0.227f + " FEET DEEP!");
		}
	}

	private void printStats() {
		writeln("Height: " + mHeight / 1000.f + "km, Velocity: " + mVelocity * 3.6f + "km/h, Fuel: " + mFuel + "kg, Capsule Weight: " + mCapsuleWeight + "kg, Gravity: " + mGravity + "m/s2");
	}
}

