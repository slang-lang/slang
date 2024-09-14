
import Node;

public abstract object Condition extends Node {
    public void Constructor( string name = "Condition" ) {
        base.Constructor( NodeType.Condition, name );
    }

    public void print() {
        print( Name );
    }

    public abstract NodeStatus tick() modify;
}
