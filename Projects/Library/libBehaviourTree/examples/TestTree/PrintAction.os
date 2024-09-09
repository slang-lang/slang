
import Nodes.Action;

public object PrintAction extends Action {
    public void Constructor( string name ) {
        base.Constructor( name );
    }

    public override NodeStatus tick() modify {
        print( "PrintAction: " + Name );

        return NodeStatus.Success;
    }
}
