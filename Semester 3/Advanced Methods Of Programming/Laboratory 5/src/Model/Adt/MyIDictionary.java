package Model.Adt;

import Exceptions.DataStructureExceptions;

import java.util.Map;
import java.util.Set;

public interface MyIDictionary<T, K> {
    boolean isDefined(T key);
    K lookup(T key) throws DataStructureExceptions;
    void update(T key, K value);
    void delete(T key) throws DataStructureExceptions;
    String toString();
    void clear();
    Map<T, K> getContent();
    MyIDictionary<T, K> deepCopy();
}
