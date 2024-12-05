package Model.Values;

import Model.Type.BoolType;
import Model.Type.IType;

public class BoolValue implements IValue{
    private boolean value;
    public BoolValue() {
        this.value = false;
    }
    public BoolValue(boolean value) {
        this.value = value;
    }
    public IType getType() {
        return new BoolType();
    }
    public boolean equals(IValue other){
        IType valueType = other.getType();
        if(!valueType.equals(this.getType()))
            return false;
        return ((BoolValue) other).getValue() == value;
    }
    public String toString() {
        return "Boolean: " + value;
    }

    @Override
    public IValue deepCopy() {
        return new BoolValue(value);
    }

    public IValue defaultValue(){
        return new BoolValue(false);
    }
    public boolean getValue() {
        return value;
    }
}
