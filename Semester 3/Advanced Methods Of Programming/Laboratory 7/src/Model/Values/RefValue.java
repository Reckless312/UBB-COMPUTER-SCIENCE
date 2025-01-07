package Model.Values;

import Model.Type.IType;
import Model.Type.RefType;

public class RefValue implements IValue {
    private int address;
    private IType locationType;

    public RefValue(int address, IType locationType) {
        this.address = address;
        this.locationType = locationType;
    }

    public IType getType() {
        return new RefType(locationType);
    }

    public int getAddress() {
        return address;
    }

    public boolean equals(IValue value) {
        if (!value.getType().equals(locationType)){
            return false;
        }
        RefValue refValue = (RefValue) value;
        return address == refValue.address;
    }

    public IValue deepCopy() {
        return new RefValue(address, this.locationType.deepCopy());
    }

    public String toString() {
        return "Reference to type: " + locationType.toString() + " at address: " + address;
    }
}
