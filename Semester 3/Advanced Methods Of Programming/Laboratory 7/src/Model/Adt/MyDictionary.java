package Model.Adt;

import Exceptions.DataStructureExceptions;

import java.util.Map;
import java.util.HashMap;
import java.util.concurrent.ConcurrentHashMap;

public class MyDictionary<T, K> implements MyIDictionary<T, K>{
    private Map<T, K> dictionary;

    public MyDictionary() {
        dictionary = new ConcurrentHashMap<>();
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

    public void delete(T key) {
        if(!this.dictionary.containsKey(key)){
            throw new DataStructureExceptions("Key not found");
        }

        this.dictionary.remove(key);
    }

    public String toString() {
        StringBuilder result = new StringBuilder();

        for (Map.Entry<T, K> entry : this.dictionary.entrySet()) {
            result.append("{ ").append(entry.getKey().toString()).append(" --> ").append(entry.getValue().toString()).append(" }").append("\n");
        }

        return result.toString();
    }

    public void clear() {
        this.dictionary.clear();
    }

    public Map<T, K> getContent() {
        return this.dictionary;
    }

    public MyIDictionary<T, K> deepCopy() {
        Map<T, K> result = new HashMap<>(this.dictionary);
        return new MyDictionary<>(result);
    }
}
