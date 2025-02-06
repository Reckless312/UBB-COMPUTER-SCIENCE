package Model.Adt;

public class Pair<T, K> implements IPair<T, K>{
    private T Index;
    private K Program;

    public Pair(T Index, K Program) {
        this.Index = Index;
        this.Program = Program;
    }

    public T getIndex() {
        return Index;
    }

    public K getProgram() {
        return Program;
    }

    public String toString() {
        return "Pair [Index=" + Index + ", Program=" + Program + "]";
    }
}
