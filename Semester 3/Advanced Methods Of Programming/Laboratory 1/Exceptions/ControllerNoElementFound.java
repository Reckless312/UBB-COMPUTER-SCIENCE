package Exceptions;

public class ControllerNoElementFound extends RuntimeException {
    public ControllerNoElementFound(String message) {
        super(message);
    }
}
