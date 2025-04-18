package Model.Statements;

import Exceptions.ExpressionException;
import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.Adt.MyIList;
import Model.Expressions.IExpression;
import Model.ProgramState.ProgramState;
import Model.Values.IValue;

public class PrintStatement implements IStatement{
    private IExpression expression;

    public PrintStatement(IExpression expression){
        this.expression = expression;
    }

    public String toString() {
        return "(Print(" + expression.toString() + "))";
    }

    public ProgramState execute(ProgramState currentState) throws StatementException, ExpressionException {
        MyIList<IValue> out = currentState.getOut();
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heap = currentState.getHeap();
        IValue value = this.expression.evaluate(symbolTable, heap);
        out.add(value);
        return currentState;
    }

    @Override
    public IStatement deepCopy() {
        return new PrintStatement(expression.deepCopy());
    }
}
