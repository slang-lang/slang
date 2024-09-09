
// library imports
import System.Collections.Vector;

// project imports
import Node;


public object Factory {
    public void Constructor() {
        Nodes = new Vector<Node>();
    }

    public Node getNode( string name ) throws {
        foreach ( Node node : Nodes ) {
            if ( node.Name == name ) {
                return Node;
            }
        }

        throw "Unknown node '" + name + "' requested!";
    }

    public void registerNode( Node node ) modify throws {
        if ( Nodes.contains( node ) ) {
            throw "duplicate node '" + node.Name + "' added!";
        }

        Nodes.push_back( node );
    }

    private Vector<Node> Nodes;
}
