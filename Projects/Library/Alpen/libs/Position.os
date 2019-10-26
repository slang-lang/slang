
// library imports

// project imports


public object Position {
    public int levelID;
    public int positionID;

    public void Constructor() {
        // this is empty by intend
    }

    public void Constructor(int _levelID, int _positionID) {
        levelID = _levelID;
        positionID = _positionID;
    }

    public bool operator==(Position other const) const {
        return levelID == other.levelID && positionID == other.positionID;
    }

    public string =operator(string) const {
        return "Position { levelID: " + levelID + ", positionID: " + positionID + " }";
    }
}
