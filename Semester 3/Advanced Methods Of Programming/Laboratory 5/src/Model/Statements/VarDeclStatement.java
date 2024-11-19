package Model.Statements;

import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.ProgramState.ProgramState;
import Model.Type.IType;
import Model.Values.IValue;

public class VarDeclStatement implements IStatement{
    private String variableName;
    private IType variableType;

    public VarDeclStatement(String variableName, IType variableType) {
        this.variableName = variableName;
        this.variableType = variableType;
    }

    public ProgramState execute(ProgramState currentState) throws StatementException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        if(symbolTable.isDefined(this.variableName)){
            throw new StatementException("Variable name already exists");
        }
        symbolTable.update(this.variableName, variableType.defaultValue());
        return currentState;
    }

    @Override
    public IStatement deepCopy() {
        return new VarDeclStatement(this.variableName, this.variableType.deepCopy());
    }

    public String toString(){
        return "(" + variableType.toString() + " " + variableName + ")";
    }
}
