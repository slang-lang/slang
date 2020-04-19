#!/usr/local/bin/slang

public void Main(int argc, string args) {
	Towers1();
	Towers2();
}

private void Towers1() {
	print("Towers 1:");

	int nDisks = 3;

	doTowers(nDisks, "A", "B", "C");
}

private void Towers2() {
	print("Towers 2:");

	move(5, 1, 3);
}

private void doTowers(int topN, string from, string inter, string to) {
	if ( topN == 1 ) {
		print("Disk 1 from " + from + " to " + to);
	}
	else {
		doTowers(topN - 1, from, to, inter);
		print("Disk " + topN + " from " + from + " to " + to);
		doTowers(topN - 1, inter, from, to);
	}
}

private void move(int n, int startPole, int endPole) {
	if ( !n ) {
		return;
	}

	int intermediatePole = 6 - startPole - endPole;
	move(n - 1, startPole, intermediatePole);
	print("Move " + n + " from " + startPole + " to " + endPole);
	move(n - 1, intermediatePole, endPole);
}

