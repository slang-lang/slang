
// library imports
import System.Collections.Vector;

// project imports
import libs.Position;


public object MoveShuttle {
	public string shuttleID;
	public Vector<Position> wayPoints;

	public void Constructor() {
		wayPoints = new Vector<Position>();
	}

	public string toString() const {
		string result = "shuttleID: " + shuttleID;

		foreach ( Position pos : wayPoints ) {
			result += ", " + cast<string>(pos);
		}

		return result;
	}
}

