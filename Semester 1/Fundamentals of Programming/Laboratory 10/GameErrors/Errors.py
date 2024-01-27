class GameError(Exception):
    def __init__(self, error_message):
        self.message = error_message


class BoardError(GameError):
    def __init__(self, error_message):
        super().__init__(error_message)
