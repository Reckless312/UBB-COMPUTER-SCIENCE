package Model.Statements;

import Exceptions.DataStructureExceptions;
import Exceptions.ExpressionException;
import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.Expressions.IExpression;
import Model.ProgramState.ProgramState;
import Model.Type.IType;
import Model.Type.RefType;
import Model.Values.IValue;
import Model.Values.RefValue;

public class HeapAllocationStatement implements IStatement {
    private String variableName;
    private IExpression expression;

    public HeapAllocationStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    public ProgramState execute(ProgramState currentState) throws StatementException, DataStructureExceptions, ExpressionException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        if(!symbolTable.isDefined(variableName)){
            throw new StatementException("Variable " + variableName + " not defined");
        }

        IValue value = symbolTable.lookup(variableName);
        IType valueType = value.getType();

        if(!(valueType instanceof RefType)){
            throw new StatementException("Value of variable " + variableName + " is not of type " + valueType.toString());
        }

        MyIHeap heap = currentState.getHeap();

        IValue evaluate = this.expression.evaluate(symbolTable, heap);
        IType evaluateType = evaluate.getType();
        if(!((RefType) valueType).getInner().equals(evaluateType)){
            throw new StatementException("Value of variable " + variableName + " is not of type " + evaluateType.toString());
        }

        synchronized (heap) {
            heap.addToNewAddress(evaluate);
        }

        symbolTable.update(variableName, new RefValue(heap.getLastAddedAddress(), ((RefType)valueType).getInner()));

        return null;
    }

    public String toString() {
        return "Allocate in heap: " + variableName + " -> " + this.expression.toString();
    }

    public IStatement deepCopy() {
        return new HeapAllocationStatement(this.variableName, this.expression.deepCopy());
    }

    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnv) throws StatementException, DataStructureExceptions {
        IType typeVariable = typeEnv.lookup(this.variableName);
        IType typeExpression = this.expression.typeCheck(typeEnv);
        if (typeVariable.equals(new RefType(typeExpression))) {
            return typeEnv;
        }
        else{
            throw new StatementException("Heap Allocation Statement Error: Different types found");
        }
    }
}
