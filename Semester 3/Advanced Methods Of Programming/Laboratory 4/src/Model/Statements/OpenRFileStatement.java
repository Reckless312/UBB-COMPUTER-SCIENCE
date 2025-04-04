package Model.Statements;

import Exceptions.ExpressionException;
import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.Expressions.IExpression;
import Model.ProgramState.ProgramState;
import Model.Type.IType;
import Model.Type.StringType;
import Model.Values.IValue;
import Model.Values.StringValue;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class OpenRFileStatement implements IStatement{
    private IExpression expression;

    public OpenRFileStatement(IExpression expression) {
        this.expression = expression;
    }

    public ProgramState execute(ProgramState currentState) throws StatementException, ExpressionException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heap = currentState.getHeap();
        IValue evaluate = this.expression.evaluate(symbolTable, heap);
        IType evaluateType = evaluate.getType();

        if(!evaluateType.equals(new StringType())){
            throw new StatementException("Name of the file must be a string!");
        }

        MyIDictionary<IValue, BufferedReader> fileTable = currentState.getFileTable();
        if(fileTable.isDefined(evaluate)){
            throw new StatementException("File already opened");
        }

        BufferedReader buffer;
        try{
            buffer = new BufferedReader(new FileReader(((StringValue)evaluate).getValue()));
        }
        catch(IOException e){
            throw new StatementException("Error opening file");
        }

        fileTable.update(evaluate, buffer);
        return currentState;
    }

    public IStatement deepCopy() {
        return new OpenRFileStatement(expression.deepCopy());
    }

    public String toString(){
        return "(Open file: '" + expression.toString() + "')";
    }
}
