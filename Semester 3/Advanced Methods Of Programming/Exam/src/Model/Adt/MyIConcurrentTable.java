package Model.Adt;

import Exceptions.DataStructureExceptions;

import java.util.Map;

public interface MyIConcurrentTable<K>{
    void add(K value);
    void clear();
    Integer previouslyAddedLocation();
    K lookup(Integer location) throws DataStructureExceptions;
    Map<Integer, K> getMap();
    void changeAtLocation(Integer location, K value) throws DataStructureExceptions;
}
