
// library imports

// project imports
import Position;


public enum JobState {
	New = 1,
	Started,
	Done,
	Cancelled;
}

public enum JobType {
	Park = 1,
	Get,
	Put,
	Wait;
}

public object Job {
    public int jobID;
    public JobType typeID;
    public int levelID;
    public int orderID;
    public Position position;
    public int sequence;
    public int shuttleID;
    public JobState stateID;

    // For testing only - begin
    public int endTime;
    public int startTime;
    // For testing only - end;

    public void Constructor() {
        position = new Position();
    }

    public Job Copy() const {
        Job result = new Job();

        result.jobID = jobID;
        result.typeID = typeID;
        result.levelID = levelID;
        result.orderID = orderID;
        result.position = copy position;
        result.sequence = sequence;
        result.shuttleID = shuttleID;
        result.stateID = stateID;

        // For testing only - begin
        result.endTime = endTime;
        result.startTime = startTime;
        // For testing only - end

        return result;
    }

    public string =operator(string) const {
        return "Job { jobID: " + jobID +
                ", typeID: " + cast<string>( typeID ) +
                ", stateID: " + cast<string>( stateID ) +
                ", shuttleID: " + shuttleID +
                ", orderID: " + orderID +
                ", position: " + cast<string>(position) +
                ", sequence: " + sequence +
                ", startTime: " + startTime +
                ", endTime: " + endTime +
                " }";
    }
}

