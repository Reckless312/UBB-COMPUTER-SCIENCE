from src.DomainServices.Command import Command
from src.Errors.UndoRedoError import UndoRedoError


class Operation:
    def __init__(self, undo_command: Command, redo_command: Command):
        self.__undo = undo_command
        self.__redo = redo_command

    def undo(self):
        return self.__undo()

    def redo(self):
        return self.__redo()


class UndoRedoService:
    def __init__(self):
        self.__undo = []
        self.__redo = []

    def register(self, operation: Operation):
        self.__undo.append(operation)

    def undo(self):
        if not self.__undo:
            raise UndoRedoError("No more undoes!")
        operation = self.__undo.pop()
        self.__redo.append(operation)
        operation.undo()

    def redo(self):
        if not self.__redo:
            raise UndoRedoError("No more redoes!")
        operation = self.__redo.pop()
        self.__undo.append(operation)
        operation.redo()
