package Model.Adt;

import Exceptions.DataStructureExceptions;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class MyLockTable<K> implements MyIConcurrentTable<K>{
    private Map<Integer, K> map;
    private Integer newAddress;

    public MyLockTable() {
        map = new ConcurrentHashMap<>();
        newAddress = 0;
    }

    public void add(K value) {
        newAddress++;
        map.put(newAddress, value);
    }

    public void clear() {
        map.clear();
    }

    public Integer previouslyAddedLocation() {
        return newAddress;
    }

    public K lookup(Integer location) throws DataStructureExceptions {
        if (map.containsKey(location)) {
            return map.get(location);
        }
        throw new DataStructureExceptions("No such location");
    }

    public Map<Integer, K> getMap() {
        return map;
    }

    public void changeAtLocation(Integer location, K value) throws DataStructureExceptions {
        if (!map.containsKey(location)) {
            throw new DataStructureExceptions("No such location");
        }
        map.put(location, value);
    }

    public String toString() {
        StringBuilder result = new StringBuilder();

        for (Map.Entry<Integer, K> entry : this.map.entrySet()) {
            result.append("{ ").append(entry.getKey().toString()).append(" --> ").append(entry.getValue().toString()).append(" }").append("\n");
        }

        return result.toString();
    }
}
