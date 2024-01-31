from src.Errors import GameError
from src.Game import Game


class Service:
    def __init__(self, snake: Game):
        self.game = snake

    def prepare_move(self, user_input: str):
        """
        Check if the move is correct one and makes move on the board
        :param user_input: int
        :return: None
        """
        move = user_input[5:]
        if move == "":
            move = 1
        try:
            move = int(move)
        except ValueError:
            raise GameError("Not an integer!")
        self.game.make_move(move)

    def change_direction(self, user_input: str):
        """
        Checks if the directions is correct and changes it
        :param user_input: str
        :return: None
        """
        directions = ["up", "right", "down", "left"]
        if user_input not in directions:
            raise GameError("Not a direction!")
        current_direction = self.game.direction
        if current_direction == "up" and user_input == "down":
            raise GameError("180 direction.")
        elif current_direction == "right" and user_input == "left":
            raise GameError("180 direction.")
        elif current_direction == "left" and user_input == "right":
            raise GameError("180 direction.")
        elif current_direction == "down" and user_input == "up":
            raise GameError("180 direction.")
        self.game.change_direction(user_input)

    def prepare_to_print(self):
        """
        :return: The Board
        """
        return str(self.game)
