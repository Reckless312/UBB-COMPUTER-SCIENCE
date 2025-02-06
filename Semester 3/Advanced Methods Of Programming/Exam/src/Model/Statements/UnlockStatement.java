package Model.Statements;

import Exceptions.DataStructureExceptions;
import Exceptions.StatementException;
import Model.Adt.MyIConcurrentTable;
import Model.Adt.MyIDictionary;
import Model.ProgramState.ProgramState;
import Model.Type.IType;
import Model.Type.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;

public class UnlockStatement implements IStatement {
    private String id;

    public UnlockStatement(String id) {
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
        synchronized(lockTable){
            Integer identifier = lockTable.lookup(((IntValue)value).getValue());
            if (identifier == currentState.getId()) {
                lockTable.changeAtLocation(((IntValue)value).getValue(), -1);
            }
        }
        return null;
    }

    public IStatement deepCopy() {
        return new UnlockStatement(id);
    }

    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnv) throws StatementException, DataStructureExceptions {
        IType type = typeEnv.lookup(id);
        if (!type.equals(new IntType())){
            throw new StatementException("Value type is not IntType");
        }
        return typeEnv;
    }

    public String toString() {
        return "Unlock (" + id + ")";
    }
}
