package Repository;

import Exceptions.RepositoryException;
import Model.ProgramState.ProgramState;

public interface IRepository {
    ProgramState getProgramState() throws RepositoryException;
    void setProgramState(ProgramState programState);
    void logPrgStateExec() throws RepositoryException;
}
