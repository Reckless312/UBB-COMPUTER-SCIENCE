package Model.Adt;

import Exceptions.DataStructureExceptions;
import Model.Values.IValue;

import java.util.Map;

public interface MyIHeap {
    boolean isValid(Integer address);
    void addToNewAddress(IValue value);
    void addToAddress(Integer address, IValue value);
    boolean checkAddress(Integer address);
    Integer getLastAddedAddress();
    IValue getValueFromAddress(Integer address) throws DataStructureExceptions;
    void setContent(Map<Integer, IValue> content);
    Map<Integer, IValue> getContent();
    void clear();
}
