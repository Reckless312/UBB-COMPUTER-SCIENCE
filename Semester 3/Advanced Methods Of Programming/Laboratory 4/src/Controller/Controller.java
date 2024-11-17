package Controller;

import Exceptions.ControllerException;
import Exceptions.DataStructureExceptions;
import Exceptions.RepositoryException;
import Exceptions.StatementException;
import Model.Adt.*;
import Model.ProgramState.ProgramState;
import Model.Statements.*;
import Model.Values.IValue;
import Model.Values.RefValue;
import Repository.IRepository;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Controller {
    private IRepository repo;
    private int displayFlag;

    public Controller(IRepository repo, int displayFlag) {
        this.repo = repo;
        this.displayFlag = displayFlag;
    }

    public Map<Integer, IValue> unsafeGarbageCollector(List<Integer> symTableAddresses, List<Integer> heapTableAddresses, Map<Integer, IValue> heap){
        Map<Integer, IValue> inUseFromSymTable = heap.entrySet().stream()
                .filter(entry->symTableAddresses.contains(entry.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
        List<Integer> referentialValuesInHeap = this.getAddressesFromTable(inUseFromSymTable.values());
        return Stream.concat(inUseFromSymTable.entrySet().stream(),
                        heap.entrySet().stream()
                                .filter(entry->referentialValuesInHeap.contains(entry.getKey())))
                .distinct()
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public List<Integer> getAddressesFromTable(Collection<IValue> tableValues){
        return tableValues.stream()
                .filter(v->v instanceof RefValue)
                .map(v->{RefValue v1 = (RefValue) v; return v1.getAddress();})
                .collect(Collectors.toList());
    }

    public void oneStep(ProgramState state) throws ControllerException, DataStructureExceptions, StatementException {
        MyIStack<IStatement> exeStack = state.getExeStack();
        if(exeStack.empty())
            throw new ControllerException("ExeStack is empty");
        IStatement statement = exeStack.pop();
        statement.execute(state);
    }

    public void allStep() throws RepositoryException, ControllerException, DataStructureExceptions, StatementException {
        ProgramState state = repo.getProgramState();
        this.repo.logPrgStateExec();
        switch (displayFlag) {
            case 0:
                while (!state.getExeStack().empty()) {
                    this.oneStep(state);
                    this.repo.logPrgStateExec();
                    state.getHeap().setContent(this.unsafeGarbageCollector(this.getAddressesFromTable(state.getSymbolTable().getContent().values()),this.getAddressesFromTable(state.getHeap().getContent().values()), state.getHeap().getContent()));
                }
                System.out.println(state.toString());
                break;
            case 1:
                System.out.println(state.toString());
                while(!state.getExeStack().empty()) {
                    this.oneStep(state);
                    this.repo.logPrgStateExec();
                    state.getHeap().setContent(this.unsafeGarbageCollector(this.getAddressesFromTable(state.getSymbolTable().getContent().values()),this.getAddressesFromTable(state.getHeap().getContent().values()), state.getHeap().getContent()));
                    System.out.println(state.toString());
                }
                break;
            default:
                break;
        }
    }

    public void clearState(){
        ProgramState state = repo.getProgramState();
        state.clear();
    }
}
