
import Node;

public abstract object Action extends Node {
    public void Constructor( string name = "Action" ) {
        base.Constructor( NodeType.Action, name );
    }

    public void print() {
        print( Name );
    }

    public abstract NodeStatus tick() modify;
}
