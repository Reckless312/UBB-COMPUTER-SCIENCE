package Model.ProgramState;

import Exceptions.ProgramStateException;
import Model.Adt.*;
import Model.Statements.IStatement;
import Model.Values.IValue;

import java.io.BufferedReader;

public class ProgramState {
    private MyIStack<IStatement> exeStack;
    private MyIDictionary<String, IValue> symbolTable;
    private MyIList<IValue> out;
    private IStatement originalProgram;
    private MyIDictionary<IValue, BufferedReader> FileTable;
    private MyIHeap heap;
    private int id;
    private static int generalId = 0;

    public ProgramState(MyIStack<IStatement> exeStack, MyIDictionary<String, IValue> symbolTable, MyIList<IValue> out, MyIDictionary<IValue, BufferedReader> FileTable,
                        MyIHeap heap, IStatement originalProgram) {
        this.exeStack = exeStack;
        this.symbolTable = symbolTable;
        this.out = out;
        this.exeStack.push(originalProgram);
        this.originalProgram = originalProgram.deepCopy();
        this.FileTable = FileTable;
        this.heap = heap;
        this.id = idChange();

    }

    public void clear(){
        this.exeStack.clear();
        this.symbolTable.clear();
        this.FileTable.clear();
        this.out.clear();
        this.heap.clear();
        this.exeStack.push(originalProgram);
        this.originalProgram = originalProgram.deepCopy();
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

    public MyIDictionary<IValue, BufferedReader> getFileTable() {
        return this.FileTable;
    }

    public void setFileTable(MyIDictionary<IValue, BufferedReader> FileTable) {
        this.FileTable = FileTable;
    }

    public MyIHeap getHeap() {
        return this.heap;
    }

    public void setHeap(MyIHeap heap) {
        this.heap = heap;
    }

    public String BinaryTreeFromExeStack(MyIStack<IStatement> executionStack) {
        ITreeBuilder<IStatement> treeBuilder = new BinaryTreeBuilder();
        StringBuilder stringBuilder = new StringBuilder();
        MyStack<IStatement> exeStack = (MyStack<IStatement>) executionStack;
        for(IStatement statement: exeStack.getStack().reversed()){
            MyIBinaryTree<IStatement> currentTree = treeBuilder.buildTree(statement);
            StringBuilder subtreeStringBuilder = currentTree.treeTraversal();
            stringBuilder.append(subtreeStringBuilder);
        }
        return stringBuilder.toString();
    }

    public String toString() {
        StringBuilder result = new StringBuilder();
        result.append("Program id: ").append(id).append("\n");
        result.append("Execution Stack:\n");
        result.append(this.BinaryTreeFromExeStack(this.exeStack));
        result.append("------------------------------------------------------------------------\n");
        result.append("Symbol table:\n");
        result.append(this.symbolTable.toString());
        result.append("------------------------------------------------------------------------\n");
        result.append("Out:\n");
        result.append(this.out);
        result.append("------------------------------------------------------------------------\n");
        result.append("FileTable:\n");
        result.append(this.FileTable.toString());
        result.append("------------------------------------------------------------------------\n");
        result.append("Heap:\n");
        result.append(this.heap.toString());
        result.append("#########################################################################");
        return result.toString();
    }

    public Boolean isNotCompleted(){
        return !this.exeStack.empty();
    }

    public ProgramState oneStep() throws ProgramStateException {
        if(this.exeStack.empty()){
            throw new ProgramStateException("ExeStack is empty");
        }
        IStatement statement = this.exeStack.pop();
        return statement.execute(this);
    }

    public synchronized static int idChange(){
        return generalId++;
    }

    public int getId() {
        return this.id;
    }
}
