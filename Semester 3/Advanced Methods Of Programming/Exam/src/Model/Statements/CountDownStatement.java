package Model.Statements;

import Exceptions.DataStructureExceptions;
import Exceptions.StatementException;
import Model.Adt.MyIConcurrentTable;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.Adt.MyIList;
import Model.ProgramState.ProgramState;
import Model.Type.IType;
import Model.Type.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;

public class CountDownStatement implements IStatement {
    private String id;

    public CountDownStatement(String id) {
        this.id = id;
    }

    public ProgramState execute(ProgramState currentState) throws StatementException, DataStructureExceptions {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heap = currentState.getHeap();
        MyIConcurrentTable<Integer> latchTable = currentState.getLatchTable();
        MyIList<IValue> out = currentState.getOut();
        IValue index = symbolTable.lookup(id);
        IType type = index.getType();
        if(!type.equals(new IntType())){
            throw new StatementException("The type of index is not IntType");
        }
        synchronized (latchTable) {
            Integer value = latchTable.lookup(((IntValue) index).getValue());
            if(value > 0){
                latchTable.changeAtLocation(((IntValue) index).getValue(), value - 1);
            }
            synchronized (out){
                out.add(new IntValue(currentState.getId()));
            }
        }
        return null;
    }

    public IStatement deepCopy() {
        return new CountDownStatement(id);
    }

    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnv) throws StatementException, DataStructureExceptions {
        IType type = typeEnv.lookup(id);
        if(!type.equals(new IntType())){
            throw new StatementException("The type of index is not IntType");
        }
        return typeEnv;
    }

    public String toString() {
        return "CountDownStatement( " + id + ")";
    }
}
