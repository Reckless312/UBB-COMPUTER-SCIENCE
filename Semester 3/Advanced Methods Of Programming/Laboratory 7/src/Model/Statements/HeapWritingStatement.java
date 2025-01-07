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

public class HeapWritingStatement implements IStatement{
    private String variableName;
    private IExpression expression;

    public HeapWritingStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    public ProgramState execute(ProgramState currentState) throws StatementException, DataStructureExceptions, ExpressionException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heap = currentState.getHeap();
        IValue value = symbolTable.lookup(variableName);
        IType valueType = value.getType();

        if(!(value instanceof RefValue))
        {
            throw new StatementException("The variable '" + variableName + "' is not of type " + valueType);
        }
        Integer address = ((RefValue)value).getAddress();
        synchronized (heap) {
            if (!heap.checkAddress(address)) {
                throw new StatementException("The heap address '" + address + "' is not valid");
            }
            IValue evaluate = this.expression.evaluate(symbolTable, heap);

            if(!evaluate.getType().equals(((RefType)valueType).getInner())){
                throw new StatementException("The variable '" + variableName + "' is not of type " + evaluate.getType());
            }
            heap.addToAddress(address, evaluate);
        }
        return null;
    }

    public IStatement deepCopy() {
        return new HeapWritingStatement(variableName, expression.deepCopy());
    }

    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnv) throws StatementException, DataStructureExceptions {
        IType valueType = typeEnv.lookup(variableName);
        IType expressionType = expression.typeCheck(typeEnv);
        if(valueType instanceof RefType){
            if(expressionType.equals(((RefType)valueType).getInner())){
                return typeEnv;
            }
            else{
                throw new StatementException("Heap Writing: Different type found");
            }
        }
        else {
            throw new StatementException("Heap Writing Error: Not a reference");
        }
    }

    public String toString() {
        return "Write in heap: " + variableName + " -> " + this.expression.toString();
    }
}
