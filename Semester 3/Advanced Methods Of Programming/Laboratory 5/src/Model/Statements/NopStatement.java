package Model.Statements;

import Exceptions.StatementException;
import Model.ProgramState.ProgramState;

public class NopStatement implements IStatement {
    public ProgramState execute(ProgramState currentState) throws StatementException {
        return null;
    }

    public IStatement deepCopy() {
        return new NopStatement();
    }

    public String toString() {
        return "Nop";
    }
}
