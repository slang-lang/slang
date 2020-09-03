
// library imports

// project imports
import Position;


public object Path {
    public Position start const;
    public Position end const;

    public void Constructor(Position _start const, Position _end const) {
        start = _start;
        end = _end;
    }

    public string =operator( string ) const {
        return "Path { start: " + cast<string>( start ) + ", end: " + cast<string>( end ) + " }";
    }
}
