package Model.Statements;

import Exceptions.DataStructureExceptions;
import Exceptions.ExpressionException;
import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.Expressions.IExpression;
import Model.ProgramState.ProgramState;
import Model.Type.IType;
import Model.Type.IntType;
import Model.Type.StringType;
import Model.Values.IValue;
import Model.Values.IntValue;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStatement implements IStatement {
    private IExpression expression;
    private String variableName;

    public ReadFileStatement(IExpression expression, String variableName) {
        this.expression = expression;
        this.variableName = variableName;
    }

    public ProgramState execute(ProgramState currentState) throws StatementException, DataStructureExceptions, ExpressionException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        IValue value = symbolTable.lookup(this.variableName);
        IType valueType = value.getType();

        if(!valueType.equals(new IntType())) {
            throw new StatementException("Variable '" + this.variableName + "' is not of type Int");
        }

        IValue evaluate = this.expression.evaluate(symbolTable);
        if(!evaluate.getType().equals(new StringType())) {
            throw new StatementException("Variable '" + this.variableName + "' is not of type String");
        }

        MyIDictionary<IValue, BufferedReader> fileTable = currentState.getFileTable();
        BufferedReader buffer;
        try{
            buffer = fileTable.lookup(evaluate);
        }
        catch(DataStructureExceptions e){
            throw new StatementException("File name not found");
        }

        try {
            String line = buffer.readLine();
            IntValue intValue;
            if(line == null) {
                intValue = new IntValue(0);
            }
            else {
                intValue = new IntValue(Integer.parseInt(line));
            }
            symbolTable.update(this.variableName, intValue);
        } catch (IOException | NumberFormatException e) {
            throw new StatementException("Error reading file");
        }

        return currentState;
    }

    public IStatement deepCopy() {
        return new ReadFileStatement(this.expression.deepCopy(), this.variableName);
    }

    public String toString() {
        return "(Read from file: '" + this.expression.toString() + "')";
    }
}
