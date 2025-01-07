package Model.Pairs;

import Model.Values.IValue;

public class AddressIValue {
    private int address;
    private IValue value;

    public AddressIValue(int address, IValue value){
        this.address = address;
        this.value = value;
    }

    public int getAddress() {
        return address;
    }

    public IValue getValue(){
        return value;
    }
}
