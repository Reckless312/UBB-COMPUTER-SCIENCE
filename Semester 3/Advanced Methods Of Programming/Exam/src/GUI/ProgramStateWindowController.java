package GUI;

import Exceptions.*;
import Model.Adt.IPair;
import Model.Adt.ITuple;
import Model.Adt.Pair;
import Model.Pairs.AddressIValue;
import Model.Pairs.NameIValue;
import Model.ProgramState.ProgramState;
import Model.Values.IValue;
import Model.Values.RefValue;
import Repository.IRepository;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;

import java.net.URL;
import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class ProgramStateWindowController implements Initializable {
    private IRepository repo;
    private ExecutorService executor;

    @FXML
    public TextField numProgramStates;

    @FXML
    public TableView<AddressIValue> heapTableView;

    @FXML
    public TableColumn<AddressIValue, Integer> addressColumn;

    @FXML
    public TableColumn<AddressIValue, IValue> valueColumn;

    @FXML
    public ListView<IValue> outList;

    @FXML
    public ListView<String> fileList;

    @FXML
    public ListView<Integer> programList;

    @FXML
    public TableView<NameIValue> symbolTable;

    @FXML
    public TableColumn<NameIValue, String> nameColumn;

    @FXML
    public TableColumn<NameIValue, IValue> valueColumn2;

    @FXML
    public TableView<ITuple<Integer, ObservableList<Integer>, Integer>> semaphoreTable;

    @FXML
    public TableColumn<ITuple<Integer, ObservableList<Integer>, Integer>, Integer> indexColumn;

    @FXML
    public TableColumn<ITuple<Integer, ObservableList<Integer>, Integer>, Integer> semaphoreValueColumn;

    @FXML
    public TableColumn<ITuple<Integer, ObservableList<Integer>, Integer>, ObservableList<Integer>> semaphoreValueListColumn;

    @FXML
    public TableView<IPair<Integer, Integer>> lockTable;

    @FXML
    public TableColumn<IPair<Integer, Integer>, Integer> lockIndexColumn;

    @FXML
    public TableColumn<IPair<Integer, Integer>, Integer> lockProgramColumn;

    @FXML
    public TableView<IPair<Integer, Integer>> latchTable;

    @FXML
    public TableColumn<IPair<Integer, Integer>, Integer> latchIndexColumn;

    @FXML
    public TableColumn<IPair<Integer, Integer>, Integer> latchValueColumn;

    @FXML
    public ListView<String> exeList;

    ProgramState programStateSelected;

    public ProgramStateWindowController(){}

    public void setRepo(IRepository repo){
        this.repo = repo;
        numProgramStates.setText(String.valueOf(repo.getProgramStates().size()));

        addressColumn.setCellValueFactory(new PropertyValueFactory<AddressIValue, Integer>("Address"));
        valueColumn.setCellValueFactory(new PropertyValueFactory<AddressIValue, IValue>("Value"));

        nameColumn.setCellValueFactory(new PropertyValueFactory<NameIValue, String>("Name"));
        valueColumn2.setCellValueFactory(new PropertyValueFactory<NameIValue, IValue>("Value"));

        indexColumn.setCellValueFactory(new PropertyValueFactory<ITuple<Integer, ObservableList<Integer>, Integer>, Integer>("Index"));
        semaphoreValueColumn.setCellValueFactory(new PropertyValueFactory<ITuple<Integer, ObservableList<Integer>, Integer>, Integer>("Value"));
        semaphoreValueListColumn.setCellValueFactory(new PropertyValueFactory<ITuple<Integer, ObservableList<Integer>, Integer>, ObservableList<Integer>>("ValueList"));

        lockIndexColumn.setCellValueFactory(new PropertyValueFactory<IPair<Integer, Integer>, Integer>("Index"));
        lockProgramColumn.setCellValueFactory(new PropertyValueFactory<IPair<Integer, Integer>, Integer>("Program"));

        latchIndexColumn.setCellValueFactory(new PropertyValueFactory<IPair<Integer, Integer>, Integer>("Index"));
        latchValueColumn.setCellValueFactory(new PropertyValueFactory<IPair<Integer, Integer>, Integer>("Program"));
    }

    private void updateHud(){
        ProgramState firstProgramState = repo.getProgramStates().getFirst();

        ObservableList<AddressIValue> items = FXCollections.observableArrayList();
        firstProgramState.getHeap().getContent().forEach((k, v) -> items.add(new AddressIValue(k, v)));
        heapTableView.setItems(items);

        ObservableList<ITuple<Integer, ObservableList<Integer>, Integer>> items2 = FXCollections.observableArrayList();
        firstProgramState.getSemaphoreTable().getMap().forEach((k, v) -> {items2.add(v);});
        semaphoreTable.setItems(items2);
        semaphoreTable.refresh();

        ObservableList<IPair<Integer, Integer>> items3 = FXCollections.observableArrayList();
        firstProgramState.getLockTable().getMap().forEach((k, v) -> items3.add(new Pair<Integer, Integer>(k, v)));
        lockTable.setItems(items3);

        ObservableList<IPair<Integer, Integer>> items4 = FXCollections.observableArrayList();
        firstProgramState.getLatchTable().getMap().forEach((k, v) -> items4.add(new Pair<Integer, Integer>(k, v)));
        latchTable.setItems(items4);

        outList.getItems().clear();
        outList.getItems().addAll(firstProgramState.getOut().getList());

        List<String> dataFromFileTable = Arrays.stream(firstProgramState.getFileTable().toString().split("\n")).toList();
        fileList.getItems().clear();
        fileList.getItems().addAll(dataFromFileTable);

        updateFinishedPrograms();

        updateSymbolTableAndExecutionList();
    }

    private void updateFinishedPrograms(){
        List<Integer> identifiers = new ArrayList<>();
        repo.getProgramStates().forEach(programState -> {identifiers.add(programState.getId());});
        if (programStateSelected != null){
            for(int i = 0; i < programList.getItems().size(); i++){
                if (programList.getItems().get(i) != programStateSelected.getId()){
                    programList.getItems().remove(i);
                    i--;
                }
            }
            programList.getItems().addAll(identifiers.stream().filter(s->s != programStateSelected.getId()).toList());
        }
        else{
            programList.getItems().clear();
            programList.getItems().addAll(identifiers);
        }
    }

    private void updateSymbolTableAndExecutionList(){
        if(programStateSelected != null){
            ObservableList<NameIValue> items2 = FXCollections.observableArrayList();
            programStateSelected.getSymbolTable().getContent().forEach((k, v) -> items2.add(new NameIValue(k, v)));
            symbolTable.setItems(items2);

            List<String> exeStackToString = Arrays.stream(programStateSelected.BinaryTreeFromExeStack(programStateSelected.getExeStack()).split("\n")).toList();
            exeList.getItems().clear();
            exeList.getItems().addAll(exeStackToString);
        }
    }

    private void oneStepForAllPrograms(List<ProgramState> programList) throws ControllerException, InterruptedException {
        programList.forEach(programState->repo.logPrgStateExec(programState));
        List<Callable<ProgramState>> callList = programList.stream()
                .map((ProgramState p)-> (Callable<ProgramState>)(p::oneStep)).toList();
        List<ProgramState> newProgramList = executor.invokeAll(callList).stream()
                .map(future->{try{return future.get();} catch(InterruptedException | ExecutionException |
                                                              RepositoryException | DataStructureExceptions |
                                                              StatementException |
                                                              ExpressionException e)
                {throw new ControllerException(e.toString());}}).filter(Objects::nonNull).toList();
        programList.addAll(newProgramList);
        programList.forEach(programState->repo.logPrgStateExec(programState));
    }

    public void buttonExecuteHandler() throws ControllerException, InterruptedException {
        List<ProgramState> programList = removeCompletedProgram(repo.getProgramStates());
        repo.setProgramStates(programList);

        if (programList.isEmpty()){
            alertTheUser(new Exception("Program has already finished!"));
            return;
        }

        executor = Executors.newFixedThreadPool(2);

        List<IValue> symTables = programList.stream().flatMap(programState -> programState.getSymbolTable().getContent().values().stream()).distinct().toList();
        Map<Integer, IValue> newHeap = this.unsafeGarbageCollector(this.getAddressesFromTable(symTables), programList.getFirst().getHeap().getContent());
        programList.getFirst().getHeap().setContent(newHeap);

        try {this.oneStepForAllPrograms(programList);}
        catch (ControllerException e) {alertTheUser(e);}
        finally {executor.shutdown();}

        updateHud();
    }

    private Map<Integer, IValue> unsafeGarbageCollector(List<Integer> symTableAddresses, Map<Integer, IValue> heap){
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

    private List<Integer> getAddressesFromTable(Collection<IValue> tableValues) {
        return tableValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {
                    RefValue v1 = (RefValue) v;
                    return v1.getAddress();
                })
                .collect(Collectors.toList());
    }

    private List<ProgramState> removeCompletedProgram(List<ProgramState> inProgramList){
        return inProgramList.stream().filter(ProgramState::isNotCompleted).collect(Collectors.toList());
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        programList.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<Integer>() {
            @Override
            public void changed(ObservableValue<? extends Integer> observableValue, Integer integer, Integer t1) {
                programStateSelected = repo.getProgramStateById(t1);
                updateSymbolTableAndExecutionList();
                updateFinishedPrograms();
            }
        });
    }

    public void alertTheUser(Exception e){
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Error");
        alert.setHeaderText("An exception occurred");
        alert.setContentText(e.getMessage());
        alert.showAndWait();
    }
}
