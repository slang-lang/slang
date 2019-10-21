
// library imports

// project imports
import Node;


public enum DirectionType {
	BiDirectional = 0,
	SourceToTarget,
	TargetToSource;
}

public enum EdgeType {
	TRAVERSABLE = 0;
}

public object Edge {
	public DirectionType direction;
	public int length;
	public Node source;
	public Node target;
	public EdgeType type;

	public void Constructor() {
	}

	public string =operator(string) const {
		return "Edge { Source: " + cast<string>( source ) + ", Target: " + cast<string>( target ) + ", Length: " + length + ", Type: " + cast<string>( type ) + ", Direction: " + cast<string>( direction ) + " }";
	}
}

