package Model.Adt;
import java.util.List;
import java.util.ArrayList;
public class MyList <T> implements MyIList<T>{
    private List<T> elements;

    public MyList(List<T> elements){
        this.elements = elements;
    }

    public MyList(){
        this.elements = new ArrayList<>();
    }

    public List<T> getList(){
        return this.elements;
    }

    public void add(T element){
        elements.add(element);
    }

    public String toString(){
        StringBuilder result = new StringBuilder();
        for(T element:elements){
            result.append("Printed: ").append(element.toString()).append("\n");
        }
        return result.toString();
    }

    public void clear() {
        this.elements.clear();
    }
}
