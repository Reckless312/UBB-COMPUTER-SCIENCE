package Repository;

import Exceptions.RepositoryException;
import Model.ProgramState.ProgramState;

import java.util.List;

public interface IRepository {
    void logPrgStateExec(ProgramState programState) throws RepositoryException;
    List<ProgramState> getProgramStates();
    void setProgramStates(List<ProgramState> programStates);
    void originalList();
    ProgramState getProgramStateById(Integer id);
}
