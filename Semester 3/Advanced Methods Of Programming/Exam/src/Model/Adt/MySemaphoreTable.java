package Model.Adt;

import Exceptions.DataStructureExceptions;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class MySemaphoreTable <K> implements MyIConcurrentTable<K> {
    private Map<Integer, K> map;
    private Integer newAddress;

    public MySemaphoreTable() {
        this.map = new ConcurrentHashMap<Integer, K>();
        this.newAddress = 0;
    }

    public void add(K value) {
        this.newAddress++;
        this.map.put(newAddress, value);
    }

    public void clear() {
        this.map.clear();
    }

    public Integer previouslyAddedLocation() {
        return this.newAddress;
    }

    public K lookup(Integer location) throws DataStructureExceptions {
        if (!this.map.containsKey(location)) {
            throw new DataStructureExceptions("Location '" + location + "' is not found");
        }
        return this.map.get(location);
    }

    public Map<Integer, K> getMap() {
        return this.map;
    }

    public void changeAtLocation(Integer location, K value) throws DataStructureExceptions {
        return;
    }

    public String toString() {
        StringBuilder result = new StringBuilder();

        for (Map.Entry<Integer, K> entry : this.map.entrySet()) {
            result.append("{ ").append(entry.getKey().toString()).append(" --> ").append(entry.getValue().toString()).append(" }").append("\n");
        }

        return result.toString();
    }
}
