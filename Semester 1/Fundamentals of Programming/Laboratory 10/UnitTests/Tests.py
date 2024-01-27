import unittest
from Board.Board import Board
from GameErrors.Errors import BoardError
from Computer.AI import AI
from Game.Game import Game


class Tests(unittest.TestCase):

    def setUp(self):
        self.__board = Board()
        self.__ai = AI()
        self.__game = Game()

    def test_board(self):
        self.__board.make_move(2, "red")
        self.assertEqual(self.__board.table[37], 1)
        self.__board.make_move(3, "yellow")
        self.assertEqual(self.__board.table[38], -1)
        self.__board.validator[2] = -1
        with self.assertRaises(BoardError):
            self.__board.make_move(8, "red")
            self.__board.make_move(2, "red")
            self.__board.make_move(3, "not color")
        self.assertEqual(self.__board.final_state(), 0)
        self.assertEqual(self.__board.is_board_full(), 0)
        self.assertEqual(self.__board.possible_columns(), [0, 1, 3, 4, 5, 6])

    def test_ai(self):
        self.assertEqual(self.__ai.minimax(self.__board, False, 4, -100, 100)[0] in [0, 1, 2, 3, 4, 5, 6], True)
        self.assertEqual(self.__ai.minimax(self.__board, False, 4, -100, 100)[1], 0)

    def test_game(self):
        self.__game.computer_move()
        self.__game.player_move(2)
