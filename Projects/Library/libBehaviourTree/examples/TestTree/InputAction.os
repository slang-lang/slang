
import Nodes.Action;

public object InputAction extends Action {
    public void Constructor() {
        base.Constructor( "Input" );
    }

    public override NodeStatus tick() modify {
        print( "InputAction: " + Name );

        var value = cin();
        print( "> " + value );

        if ( strlen( value ) >= 3 ) {
            return NodeStatus.Success;
        }

        return NodeStatus.Failure;
    }
}
