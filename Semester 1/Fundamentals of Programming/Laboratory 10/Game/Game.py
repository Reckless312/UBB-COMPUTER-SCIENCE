from Board.Board import Board
from Computer.AI import AI


class Game:
    def __init__(self):
        self.__board = Board()
        self.__computer = AI()

    def computer_move(self):
        self.__board.make_move(self.__computer.evaluate(self.__board), "yellow")

    def player_move(self, column: int):
        self.__board.make_move(column, "red")

    @property
    def get_board(self):
        return self.__board


if __name__ == "__main__":
    pass
