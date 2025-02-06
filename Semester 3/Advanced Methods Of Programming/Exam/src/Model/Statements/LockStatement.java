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

public class LockStatement implements IStatement {
    private String id;

    public LockStatement(String id) {
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
            if (identifier == -1) {
                lockTable.changeAtLocation(((IntValue)value).getValue(), currentState.getId());
            }
            else {
                currentState.getExeStack().push(this);
            }
        }
        return null;
    }

    public IStatement deepCopy() {
        return new LockStatement(id);
    }

    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnv) throws StatementException, DataStructureExceptions {
        IType type = typeEnv.lookup(id);
        if (!type.equals(new IntType())){
            throw new StatementException("Value type is not IntType");
        }
        return typeEnv;
    }

    public String toString() {
        return "LockStatement(" + id + ")";
    }
}
