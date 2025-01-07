package Model.Statements;

import Exceptions.DataStructureExceptions;
import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.ProgramState.ProgramState;
import Model.Type.IType;

public class NopStatement implements IStatement {
    public ProgramState execute(ProgramState currentState) throws StatementException {
        return null;
    }

    public IStatement deepCopy() {
        return new NopStatement();
    }

    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnv) throws StatementException, DataStructureExceptions {
        return typeEnv;
    }

    public String toString() {
        return "Nop";
    }
}
