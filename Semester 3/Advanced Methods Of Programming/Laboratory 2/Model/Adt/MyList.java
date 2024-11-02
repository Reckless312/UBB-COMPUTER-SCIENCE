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
        result.append("Out[");
        for(T element:elements){
            result.append(element.toString()).append(", ");
        }
        if (result.toString().endsWith(", "))
            result.delete(result.length()-2, result.length());
        return result.append("]").toString();
    }
}
