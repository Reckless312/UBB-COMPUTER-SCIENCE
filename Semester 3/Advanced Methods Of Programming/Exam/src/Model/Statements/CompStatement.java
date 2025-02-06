package Model.Statements;

import Exceptions.DataStructureExceptions;
import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIStack;
import Model.ProgramState.ProgramState;
import Model.Type.IType;

public class CompStatement implements IStatement {
    private IStatement firstStatement;
    private IStatement secondStatement;

    public CompStatement(IStatement firstStatement, IStatement secondStatement) {
        this.firstStatement = firstStatement;
        this.secondStatement = secondStatement;
    }

    public String toString(){
        return firstStatement.toString() + ", " + secondStatement.toString();
    }
    public ProgramState execute(ProgramState currentState) throws StatementException {
        MyIStack<IStatement> executionStack = currentState.getExeStack();
        executionStack.push(this.secondStatement);
        executionStack.push(this.firstStatement);
        return null;
    }

    public IStatement getFirst() {
        return firstStatement;
    }

    public IStatement getSecond() {
        return secondStatement;
    }

    public IStatement deepCopy() {
        return new CompStatement(firstStatement.deepCopy(), secondStatement.deepCopy());
    }

    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnv) throws StatementException, DataStructureExceptions {
        return this.secondStatement.typeCheck(firstStatement.typeCheck(typeEnv));
    }
}
