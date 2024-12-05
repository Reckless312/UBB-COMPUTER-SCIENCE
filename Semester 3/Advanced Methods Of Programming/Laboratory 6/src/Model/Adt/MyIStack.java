package Model.Adt;

import Exceptions.DataStructureExceptions;

import java.util.List;

public interface MyIStack<T> {
    T pop() throws DataStructureExceptions;
    void push(T element);
    boolean empty();
    String toString();
    void clear();
    List<T> reverse();
}
