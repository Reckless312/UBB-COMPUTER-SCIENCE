package Model.Statements;

import Exceptions.DataStructureExceptions;
import Exceptions.StatementException;
import Model.Adt.MyIConcurrentTable;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.ProgramState.ProgramState;
import Model.Type.IType;
import Model.Type.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;

public class NewLockStatement implements IStatement {
    private String id;

    public NewLockStatement(String id) {
        this.id = id;
    }

    public ProgramState execute(ProgramState currentState) throws StatementException, DataStructureExceptions {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIConcurrentTable<Integer> lockTable = currentState.getLockTable();
        IValue value = symbolTable.lookup(id);
        IType type = value.getType();
        if (!type.equals(new IntType())){
            throw new StatementException("Value type is not IntType");
        }
        synchronized (lockTable){
            lockTable.add(-1);
            symbolTable.update(id, new IntValue(lockTable.previouslyAddedLocation()));
        }
        return null;
    }

    public IStatement deepCopy() {
        return new NewLockStatement(id);
    }

    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnv) throws StatementException, DataStructureExceptions {
        IType type = typeEnv.lookup(id);
        if (!type.equals(new IntType())){
            throw new StatementException("Value type is not IntType");
        }
        return typeEnv;
    }

    public String toString() {
        return "NewLockStatement(" + id + ")";
    }
}
