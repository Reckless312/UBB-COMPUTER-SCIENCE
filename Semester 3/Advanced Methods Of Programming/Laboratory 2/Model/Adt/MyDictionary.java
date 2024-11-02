package Model.Adt;

import Exceptions.DataStructureExceptions;

import java.util.Map;
import java.util.HashMap;

public class MyDictionary<T, K> implements MyIDictionary<T, K>{
    private Map<T, K> dictionary;

    public MyDictionary() {
        dictionary = new HashMap<>();
    }

    public MyDictionary(Map<T, K> dictionary) {
        this.dictionary = dictionary;
    }

    public boolean isDefined(T key) {
        return this.dictionary.containsKey(key);
    }

    public K lookup(T key) throws DataStructureExceptions {
        K value = this.dictionary.get(key);
        if (value == null)
            throw new DataStructureExceptions("Key not found");
        return value;
    }

    public void update(T key, K value) {
        this.dictionary.put(key, value);
    }

    public String toString() {
        StringBuilder result = new StringBuilder();
        result.append("Symbol Table[");
        for (Map.Entry<T, K> entry : this.dictionary.entrySet()) {
            result.append("Variable name: ").append(entry.getKey().toString()).append(" ").append(entry.getValue().toString()).append(", ");
        }
        if(result.toString().endsWith(", "))
            result.delete(result.length() - 2, result.length());
        result.append("]");
        return result.toString();
    }
}
