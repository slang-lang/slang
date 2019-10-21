
// library imports
import System.Collections.List;

// project imports
import Edge;


public enum NodeType {
	NODE = 0,
	CROSSING,
	STATION,
	PARKING
}

public object Node {
	public List<Edge> edges;
	public int levelID;
	public int positionID;
	public NodeType type;

	public void Constructor() {
	}

	public string =operator(string) const {
		return "Node { LevelID: " + levelID + ", PositionID: " + positionID + ", Type: " + cast<string>( type ) + " }";
	}
}

