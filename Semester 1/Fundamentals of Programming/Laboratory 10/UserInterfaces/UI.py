from Game.Game import Game
from GameErrors.Errors import GameError


class UI:

    def __init__(self):
        self.__accept_command = "y"
        self.__refuse_command = "n"
        self.__game = None
        self.__game_board = None
        self.__player_move = True

    def start(self):
        print("Welcome to Connect Four!")
        print("Application done by @ Cora Ioan Alexandru")
        while True:
            self.start_console()
            self.print_menu_restart(self.__accept_command, self.__refuse_command)
            answer = input(">")
            if answer == self.__accept_command:
                continue
            elif answer == self.__refuse_command:
                break
            else:
                print("Invalid option. Game is closing.")
                break

    def start_console(self):
        self.__game = Game()
        self.__game_board = self.__game.get_board
        while True:
            if self.__player_move:
                try:
                    print("Players turn:")
                    print(self.__game_board)
                    column = int(input("Column = "))
                    self.__game.player_move(column)
                except (ValueError, GameError) as er:
                    print(er)
                    continue
            else:
                print("Computers turn:")
                print(self.__game_board)
                self.__game.computer_move()
            if self.__game_board.final_state() == 1:
                print(self.__game_board)
                print("Player won!")
                break
            elif self.__game_board.final_state() == -1:
                print(self.__game_board)
                print("Computer won!")
                break
            elif self.__game_board.is_board_full():
                print("Game is a draw!")
                break
            self.__player_move = not self.__player_move

    @staticmethod
    def print_menu_restart(accept_command: str, refuse_command: str):
        print("Game over. Want to restart?")
        print(f"\tYes / {accept_command}")
        print(f"\tNo / {refuse_command}")


if __name__ == "__main__":
    pass
