package Model.Type;

import Model.Values.BoolValue;
import Model.Values.IValue;

public class BoolType implements IType {
    public BoolType() {}
    public String toString() {return "Boolean";}

    public IValue defaultValue() {
        return new BoolValue();
    }

    public IType deepCopy() {
        return new BoolType();
    }

    public boolean equals(IType other){
        return(other instanceof BoolType);
    }
}
