package Model;

import Model.Adt.MyIDictionary;
import Model.Adt.MyIList;
import Model.Adt.MyIStack;
import Model.Statements.IStatement;
import Model.Values.IValue;

public class ProgramState {
    private MyIStack<IStatement> exeStack;
    private MyIDictionary<String, IValue> symbolTable;
    private MyIList<IValue> out;
    private IStatement originalProgram;

    public ProgramState(MyIStack<IStatement> exeStack, MyIDictionary<String, IValue> symbolTable, MyIList<IValue> out, IStatement originalProgram) {
        this.exeStack = exeStack;
        this.symbolTable = symbolTable;
        this.out = out;
        this.originalProgram = originalProgram.deepCopy(); // deep copy
        this.exeStack.push(originalProgram);
    }

    public MyIStack<IStatement> getExeStack() {
        return this.exeStack;
    }

    public void setExeStack(MyIStack<IStatement> exeStack) {
        this.exeStack = exeStack;
    }

    public MyIDictionary<String, IValue> getSymbolTable() {
        return this.symbolTable;
    }

    public void setSymbolTable(MyIDictionary<String, IValue> symbolTable) {
        this.symbolTable = symbolTable;
    }

    public MyIList<IValue> getOut() {
        return this.out;
    }

    public void setOut(MyIList<IValue> out) {
        this.out = out;
    }

    public IStatement getOriginalProgram() {
        return this.originalProgram;
    }

    public void setOriginalProgram(IStatement originalProgram) {
        this.originalProgram = originalProgram;
    }

    public String toString() {
        StringBuilder result = new StringBuilder();
        //result.append("Original Program[").append(this.originalProgram.toString()).append("]").append('\n');
        result.append(this.exeStack.toString()).append("\n");
        result.append(this.symbolTable.toString()).append("\n");
        result.append(this.out).append("\n");
        result.append("-------------------------------------------------------------------------\n");
        return result.toString();
    }
}
