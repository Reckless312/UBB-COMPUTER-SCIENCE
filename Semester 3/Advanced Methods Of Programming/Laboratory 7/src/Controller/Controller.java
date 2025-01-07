package Controller;

import Exceptions.*;
import Model.ProgramState.ProgramState;
import Model.Values.IValue;
import Model.Values.RefValue;
import Repository.IRepository;

import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Controller {
    private IRepository repo;
    private int displayFlag;
    private ExecutorService executor;

    public Controller(IRepository repo, int displayFlag) {
        this.repo = repo;
        this.displayFlag = displayFlag;
    }

    public Map<Integer, IValue> unsafeGarbageCollector(List<Integer> symTableAddresses, Map<Integer, IValue> heap){
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

    public List<Integer> getAddressesFromTable(Collection<IValue> tableValues) {
        return tableValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {
                    RefValue v1 = (RefValue) v;
                    return v1.getAddress();
                })
                .collect(Collectors.toList());
    }

    public void clearState(){
        this.repo.originalList();
        ProgramState state = repo.getProgramStates().getFirst();
        state.clear();
    }

    List<ProgramState> removeCompletedProgram(List<ProgramState> inProgramList){
        return inProgramList.stream().filter(ProgramState::isNotCompleted).collect(Collectors.toList());
    }

    void oneStepForAllPrograms(List<ProgramState> programList) throws ControllerException, InterruptedException {
        programList.forEach(programState->repo.logPrgStateExec(programState));
        List<Callable<ProgramState>> callList = programList.stream()
                .map((ProgramState p)-> (Callable<ProgramState>)(p::oneStep)).toList();
        List<ProgramState> newProgramList = executor.invokeAll(callList).stream()
                .map(future->{try{return future.get();} catch(InterruptedException | ExecutionException | RepositoryException | DataStructureExceptions | StatementException |
                                                              ExpressionException e)
                {throw new ControllerException(e.toString());}}).filter(Objects::nonNull).toList();
        programList.addAll(newProgramList);
        programList.forEach(programState->repo.logPrgStateExec(programState));
        repo.setProgramStates(programList);
    }

    public void allSteps() throws ControllerException, InterruptedException {
        executor = Executors.newFixedThreadPool(2);
        List<ProgramState> programList = removeCompletedProgram(repo.getProgramStates());
        programList.forEach(System.out::println);
        while(!programList.isEmpty()){
            List<IValue> symTables = programList.stream().flatMap(programState -> programState.getSymbolTable().getContent().values().stream()).distinct().toList();
            Map<Integer, IValue> newHeap = this.unsafeGarbageCollector(this.getAddressesFromTable(symTables), programList.getFirst().getHeap().getContent());
            programList.getFirst().getHeap().setContent(newHeap);
            this.oneStepForAllPrograms(programList);
            programList.forEach(System.out::println);
            programList = removeCompletedProgram(repo.getProgramStates());
        }
        executor.shutdown();
        repo.setProgramStates(programList);
    }
}
