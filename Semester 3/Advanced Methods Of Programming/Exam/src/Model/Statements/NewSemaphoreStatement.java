package Model.Statements;

import Exceptions.DataStructureExceptions;
import Exceptions.ExpressionException;
import Exceptions.StatementException;
import Model.Adt.*;
import Model.Expressions.IExpression;
import Model.ProgramState.ProgramState;
import Model.Type.IType;
import Model.Type.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

public class NewSemaphoreStatement implements IStatement{
    private String var;
    private IExpression firstExpression, secondExpression;

    public NewSemaphoreStatement(String var, IExpression firstExpression, IExpression secondExpression){
        this.var = var;
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
    }

    public ProgramState execute(ProgramState currentState) throws StatementException, ExpressionException, DataStructureExceptions {
        MyIDictionary<String, IValue> symTable = currentState.getSymbolTable();
        MyIHeap heap = currentState.getHeap();
        MyIConcurrentTable<ITuple<Integer, ObservableList<Integer>, Integer>> semaphoreTable = currentState.getSemaphoreTable();
        IValue number1 = this.firstExpression.evaluate(symTable, heap);
        IValue number2 = this.secondExpression.evaluate(symTable, heap);
        IType type1 = number1.getType();
        IType type2 = number2.getType();
        if (!type1.equals(new IntType()) || !type2.equals(new IntType())) {
            throw new StatementException("Values are not integers!");
        }
        Integer value1 = ((IntValue) number1).getValue();
        Integer value2 = ((IntValue) number2).getValue();
        synchronized (semaphoreTable) {
            semaphoreTable.add(new Tuple<>(value1, FXCollections.observableArrayList(), value2));
        }
        IValue symValue = symTable.lookup(var);
        IType symType = symValue.getType();
        if (!symType.equals(new IntType())) {
            throw new StatementException("Value is not an integer in the symbol table!");
        }
        synchronized (semaphoreTable) {
            symTable.update(var, new IntValue(semaphoreTable.previouslyAddedLocation()));
        }
        return null;
    }

    public IStatement deepCopy() {
        return new NewSemaphoreStatement(var, firstExpression.deepCopy(), secondExpression.deepCopy());
    }

    public String toString(){
        return "New Semaphore" + var + firstExpression.toString() + secondExpression.toString();
    }

    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnv) throws StatementException, DataStructureExceptions {
        IType type1 = firstExpression.typeCheck(typeEnv);
        IType type2 = secondExpression.typeCheck(typeEnv);
        if (!type1.equals(new IntType()) || !type2.equals(new IntType())) {
            throw new StatementException("Values are not integers!");
        }
        return typeEnv;
    }
}
