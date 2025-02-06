package Model.Pairs;

import Model.Values.IValue;

public class NameIValue {
    private String name;
    private IValue value;

    public NameIValue(String name, IValue value){
        this.name = name;
        this.value = value;
    }

    public String getName() {
        return name;
    }

    public IValue getValue(){
        return value;
    }
}
