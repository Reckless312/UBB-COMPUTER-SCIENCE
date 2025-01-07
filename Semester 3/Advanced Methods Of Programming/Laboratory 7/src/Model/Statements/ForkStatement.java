package Model.Statements;

import Exceptions.DataStructureExceptions;
import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIStack;
import Model.Adt.MyStack;
import Model.ProgramState.ProgramState;
import Model.Type.IType;


public class ForkStatement implements IStatement {
    private IStatement statement;

    public ForkStatement(IStatement statement) {
        this.statement = statement;
    }

    public ProgramState execute(ProgramState currentState) throws StatementException {
        return new ProgramState(new MyStack<>(), currentState.getSymbolTable().deepCopy(),
                currentState.getOut(), currentState.getFileTable(), currentState.getHeap(), this.statement);
    }

    public String toString() {
        return "Fork: " + statement.toString();
    }

    public IStatement deepCopy() {
        return new ForkStatement(statement.deepCopy());
    }

    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnv) throws StatementException, DataStructureExceptions {
        this.statement.typeCheck(typeEnv.deepCopy());
        return typeEnv;
    }
}
