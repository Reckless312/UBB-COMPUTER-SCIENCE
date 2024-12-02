package Model.Statements;

import Exceptions.StatementException;
import Model.ProgramState.ProgramState;

public interface IStatement {
    ProgramState execute(ProgramState currentState) throws StatementException;
    IStatement deepCopy();
}
