package Model.Adt;

public class Tuple<T, K, L> implements ITuple<T, K, L>{
    private T Index;
    private K ValueList;
    private L Value;

    public Tuple(T first, K second, L third) {
        this.Index = first;
        this.ValueList = second;
        this.Value = third;
    }

    public T getIndex() {
        return Index;
    }

    public K getValueList() {
        return ValueList;
    }

    public L getValue() {
        return Value;}

    public String toString() {
        return Index.toString() +  " " + Value.toString() + ValueList.toString();
    }
}
