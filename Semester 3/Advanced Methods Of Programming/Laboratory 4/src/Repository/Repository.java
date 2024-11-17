package Repository;

import Exceptions.RepositoryException;
import Model.ProgramState.ProgramState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository{
    private List<ProgramState> programStates;
    private String logFilePath;

    public Repository(String logFilePath) {
        programStates = new ArrayList<>();
        this.logFilePath = logFilePath;
    }

    public Repository(List<ProgramState> programStates, String logFilePath) {
        this.programStates = programStates;
        this.logFilePath = logFilePath;
    }

    public Repository(ProgramState programState, String logFilePath) {
        programStates = new ArrayList<>();
        programStates.add(programState);
        this.logFilePath = logFilePath;
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

    public void logPrgStateExec() throws RepositoryException {
        try (PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath, true)))) {
            logFile.println(this.getProgramState().toString());
        } catch (IOException e) {
            throw new RepositoryException("Cannot create output file!");
        }
    }
}
