package Model.ProgramState;

import Exceptions.ProgramStateException;
import Model.Adt.*;
import Model.Statements.IStatement;
import Model.Values.IValue;
import javafx.collections.ObservableList;

import java.io.BufferedReader;

public class ProgramState {
    private MyIStack<IStatement> exeStack;
    private MyIDictionary<String, IValue> symbolTable;
    private MyIList<IValue> out;
    private IStatement originalProgram;
    private MyIDictionary<IValue, BufferedReader> fileTable;
    private MyIHeap heap;
    private MyIConcurrentTable<ITuple<Integer, ObservableList<Integer>, Integer>> semaphoreTable;
    private MyIConcurrentTable<Integer> lockTable;
    private MyIConcurrentTable<Integer> latchTable;
    private int id;
    private static int generalId = 0;

    public ProgramState(MyIStack<IStatement> exeStack, MyIDictionary<String, IValue> symbolTable, MyIList<IValue> out, MyIDictionary<IValue, BufferedReader> FileTable,
                        MyIHeap heap, MyIConcurrentTable<ITuple<Integer, ObservableList<Integer>, Integer>> SemaphoreTable, MyIConcurrentTable<Integer> lockTable, MyIConcurrentTable<Integer> latchTable, IStatement originalProgram) {
        this.exeStack = exeStack;
        this.symbolTable = symbolTable;
        this.out = out;
        this.exeStack.push(originalProgram);
        this.originalProgram = originalProgram.deepCopy();
        this.fileTable = FileTable;
        this.heap = heap;
        this.semaphoreTable = SemaphoreTable;
        this.lockTable = lockTable;
        this.latchTable = latchTable;
        this.id = idChange();
    }

    public void clear(){
        this.exeStack.clear();
        this.symbolTable.clear();
        this.fileTable.clear();
        this.out.clear();
        this.heap.clear();
        this.semaphoreTable.clear();
        this.lockTable.clear();
        this.latchTable.clear();
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
        return this.fileTable;
    }

    public void setFileTable(MyIDictionary<IValue, BufferedReader> FileTable) {
        this.fileTable = FileTable;
    }

    public MyIHeap getHeap() {
        return this.heap;
    }

    public void setHeap(MyIHeap heap) {
        this.heap = heap;
    }

    public MyIConcurrentTable<ITuple<Integer, ObservableList<Integer>, Integer>> getSemaphoreTable() {
        return this.semaphoreTable;
    }

    public void setSemaphoreTable(MyIConcurrentTable<ITuple<Integer, ObservableList<Integer>, Integer>> semaphoreTable) {
        this.semaphoreTable = semaphoreTable;
    }

    public MyIConcurrentTable<Integer> getLockTable() {
        return this.lockTable;
    }

    public void setLockTable(MyIConcurrentTable<Integer> lockTable) {
        this.lockTable = lockTable;
    }

    public MyIConcurrentTable<Integer> getLatchTable() {
        return this.latchTable;
    }

    public void setLatchTable(MyIConcurrentTable<Integer> latchTable) {
        this.latchTable = latchTable;
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
        result.append(this.fileTable.toString());
        result.append("------------------------------------------------------------------------\n");
        result.append("Heap:\n");
        result.append(this.heap.toString());
        result.append("------------------------------------------------------------------------\n");
        result.append("Semaphore Table:\n");
        result.append(this.semaphoreTable.toString());
        result.append("------------------------------------------------------------------------\n");
        result.append("Lock Table:\n");
        result.append(this.lockTable.toString());
        result.append("------------------------------------------------------------------------\n");
        result.append("Latch Table:\n");
        result.append(this.latchTable.toString());
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
