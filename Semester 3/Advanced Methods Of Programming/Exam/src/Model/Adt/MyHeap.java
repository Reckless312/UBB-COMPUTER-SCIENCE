package Model.Adt;


import Exceptions.DataStructureExceptions;
import Model.Values.IValue;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class MyHeap implements MyIHeap{
    private Integer lastAddedAddress;
    private Map<Integer, IValue> map;

    public MyHeap() {
        this.map = new ConcurrentHashMap<Integer, IValue>();
        this.lastAddedAddress = 0;
    }

    public boolean isValid(Integer address) {
        return address != 0;
    }

    public void addToNewAddress(IValue value) {
        this.lastAddedAddress++;
        map.put(this.lastAddedAddress, value);
    }

    public void addToAddress(Integer address, IValue value) {
        if(this.map.containsKey(address)) {
            this.map.put(address, value);
        }
        else {
            throw new DataStructureExceptions("Address " + address + " is not valid");
        }
    }

    public boolean checkAddress(Integer address) {
        return this.map.containsKey(address);
    }

    public Integer getLastAddedAddress() {
        return this.lastAddedAddress;
    }

    public IValue getValueFromAddress(Integer address) throws DataStructureExceptions {
        if(map.containsKey(address)) {
            return map.get(address);
        }
        throw new DataStructureExceptions("Address is not valid");
    }

    public void setContent(Map<Integer, IValue> content) {
        this.map = content;
    }

    public Map<Integer, IValue> getContent() {
        return this.map;
    }

    public void clear() {
        this.map.clear();
        this.lastAddedAddress = 0;
    }

    public String toString() {
        StringBuilder result = new StringBuilder();

        for (Map.Entry<Integer, IValue> entry : this.map.entrySet()) {
            result.append("{ ").append(entry.getKey().toString()).append(" --> ").append(entry.getValue().toString()).append(" }").append("\n");
        }

        return result.toString();
    }
}
