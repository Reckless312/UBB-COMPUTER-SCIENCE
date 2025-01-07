package Repository;

import Exceptions.RepositoryException;
import Model.ProgramState.ProgramState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository {
    private List<ProgramState> programStates;
    private String logFilePath;
    private List<ProgramState> originalProgramStates;

    public Repository(String logFilePath) {
        programStates = new ArrayList<>();
        this.logFilePath = logFilePath;
        originalProgramStates = new ArrayList<>();
    }

    public Repository(List<ProgramState> programStates, String logFilePath) {
        this.programStates = programStates;
        this.logFilePath = logFilePath;
        this.originalProgramStates = new ArrayList<>();
        this.originalProgramStates.addAll(programStates);
    }

    public Repository(ProgramState programState, String logFilePath) {
        programStates = new ArrayList<>();
        programStates.add(programState);
        this.logFilePath = logFilePath;
        this.originalProgramStates = new ArrayList<>();
        this.originalProgramStates.add(programState);
    }

    public void logPrgStateExec(ProgramState programState) throws RepositoryException {
        try (PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath, true)))) {
            logFile.println(programState.toString());
        } catch (IOException e) {
            throw new RepositoryException("Cannot create output file!");
        }
    }

    public List<ProgramState> getProgramStates() {
        return this.programStates;
    }

    public void setProgramStates(List<ProgramState> programStates) {
        this.programStates = programStates;
    }

    public void originalList() {
        this.programStates.addAll(originalProgramStates);
    }

    public ProgramState getProgramStateById(Integer id) {
        return programStates.stream().filter(programState -> programState.getId() == id).findFirst().orElse(null);
    }
}