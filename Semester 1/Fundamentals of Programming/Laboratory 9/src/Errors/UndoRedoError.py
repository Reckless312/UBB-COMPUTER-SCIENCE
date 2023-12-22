class UndoRedoError(Exception):
    def __init__(self, message_error="Undo/Redo Error!"):
        self.__message = message_error
        super().__init__()

    def __str__(self):
        return f"{self.__message}"

    def __repr__(self):
        return str(self)
