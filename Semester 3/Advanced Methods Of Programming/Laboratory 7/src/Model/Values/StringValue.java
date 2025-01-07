package Model.Values;

import Model.Type.IType;
import Model.Type.StringType;

public class StringValue implements IValue {
    private String value;

    public StringValue(String value) {
        this.value = value;
    }

    public StringValue(){
        this.value = "NULL";
    }

    public IType getType() {
        return new StringType();
    }

    public String getValue() {
        return value;
    }

    public boolean equals(IValue value) {
        IType valueType = value.getType();
        if(!valueType.equals(this.getType())) {
            return false;
        }
        return ((StringValue)value).getValue().equals(this.value);
    }

    public IValue deepCopy() {
        return new StringValue(this.value);
    }

    public String toString() {
        return "String: " + this.value;
    }

    public IValue defaultValue(){
        return new StringValue("NULL");
    }
}
