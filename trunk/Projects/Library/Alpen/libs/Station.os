
// library imports

// project imports


public object Station {
    public int interactionID;
    public int levelID;
    public int positionID;
    public int stationID;
    public int stationTypeID;
    public int state;

    public Station Copy() const {
        Station result = new Station();

        result.interactionID = interactionID;
        result.levelID = levelID;
        result.positionID = positionID;
        result.stationID = stationID;
        result.stationTypeID = stationTypeID;
        result.state = state;

        return result;
    }
}

