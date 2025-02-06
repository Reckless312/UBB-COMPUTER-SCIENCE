package Model.Statements;

import Exceptions.DataStructureExceptions;
import Exceptions.StatementException;
import Model.Adt.ITuple;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIConcurrentTable;
import Model.ProgramState.ProgramState;
import Model.Type.IType;
import Model.Type.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;
import javafx.collections.ObservableList;

public class AcquireStatement  implements IStatement{
    private String variable;

    public AcquireStatement(String variable){
        this.variable = variable;
    }

    public ProgramState execute(ProgramState currentState) throws StatementException, DataStructureExceptions {
        MyIDictionary<String, IValue> symTable = currentState.getSymbolTable();
        MyIConcurrentTable<ITuple<Integer, ObservableList<Integer>, Integer>> semaphoreTable = currentState.getSemaphoreTable();
        IValue value = symTable.lookup(variable);
        IType type = value.getType();
        if (!type.equals(new IntType())){
            throw new StatementException("Variable '" + variable + "' is not of type Int");
        }
        synchronized (semaphoreTable){
            ITuple<Integer, ObservableList<Integer>, Integer> entry = semaphoreTable.lookup(((IntValue)value).getValue());
            Integer listLength = entry.getValueList().size();
            if ((entry.getIndex() - entry.getValue()) > listLength){
                if(!entry.getValueList().contains(currentState.getId())){
                    entry.getValueList().add(currentState.getId());
                }
            }
            else{
                currentState.getExeStack().push(this);
            }
        }
        return null;
    }

    public IStatement deepCopy() {
        return new AcquireStatement(variable);
    }

    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnv) throws StatementException, DataStructureExceptions {
        IType type = typeEnv.lookup(variable);
        if (!type.equals(new IntType())){
            throw new StatementException("Variable '" + variable + "' is not of type Int");
        }
        return typeEnv;
    }

    public String toString() {
        return "AcquireStatement " + variable;
    }
}
