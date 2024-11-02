package Repository;

import Exceptions.RepositoryException;
import Model.ProgramState;

import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository{
    private List<ProgramState> programStates;

    public Repository() {
        programStates = new ArrayList<>();
    }

    public Repository(List<ProgramState> programStates) {
        this.programStates = programStates;
    }

    public Repository(ProgramState programState) {
        programStates = new ArrayList<>();
        programStates.add(programState);
    }

    public ProgramState getProgramState() throws RepositoryException {
        if (!programStates.isEmpty()) {
            return this.programStates.getFirst();
        }
        throw new RepositoryException("Repository is empty");
    }

    public void setProgramState(ProgramState programState) {
        if (this.programStates.isEmpty()) {
            this.programStates.add(programState);
        }
        else {
            this.programStates.set(0, programState);
        }
    }
}
