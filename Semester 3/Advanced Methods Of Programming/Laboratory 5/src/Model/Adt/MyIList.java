package Model.Adt;

import java.util.List;

public interface MyIList <T>{
    List<T> getList();
    void add(T element);
    String toString();
    void clear();
}
