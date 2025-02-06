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

public class ReleaseStatement implements IStatement{
    private String variable;

    public ReleaseStatement(String variableName){
        this.variable = variableName;
    }

    public ProgramState execute(ProgramState currentState) throws StatementException {
        MyIDictionary<String, IValue> symTable = currentState.getSymbolTable();
        MyIConcurrentTable<ITuple<Integer, ObservableList<Integer>, Integer>> semaphoreTable = currentState.getSemaphoreTable();
        IValue value = symTable.lookup(variable);
        IType type = value.getType();
        if (!type.equals(new IntType())){
            throw new StatementException("Variable '" + variable + "' is not of type Int");
        }
        synchronized (semaphoreTable){
            ITuple<Integer, ObservableList<Integer>, Integer> entry = semaphoreTable.lookup(((IntValue)value).getValue());
            if(entry.getValueList().contains(currentState.getId())){
                for (int i = 0; i < entry.getValueList().size(); i++) {
                    if(entry.getValueList().get(i).equals(currentState.getId())){
                        entry.getValueList().remove(i);
                    }
                }
            }
        }
        return null;
    }

    public IStatement deepCopy() {
        return new ReleaseStatement(variable);
    }

    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnv) throws StatementException, DataStructureExceptions {
        IType type = typeEnv.lookup(variable);
        if (!type.equals(new IntType())){
            throw new StatementException("Variable '" + variable + "' is not of type Int");
        }
        return typeEnv;
    }

    public String toString(){
        return "Release " + variable;
    }
}
