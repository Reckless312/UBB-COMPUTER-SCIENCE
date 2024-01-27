from Errors import ServiceError
from Game import Game
from Services import Services


class UI:
    def __init__(self, service: Services, game: Game):
        self.service = service
        self.game = game
        self.add_command = "1"
        self.start_game = "2"
        self.exit_command = "0"

    def start(self):
        print("Hangman @2023")
        while True:
            print("Select option: ")
            print(f"Add a sentence to the game / {self.add_command}.")
            print(f"Start the game / {self.start_game}.")
            print(f"Exit the game / {self.exit_command}.")
            start_command = input(">")
            if start_command == self.add_command:
                try:
                    proposition = input("Insert proposition: ")
                    self.service.add(proposition)
                except ServiceError as se:
                    print(se)
            elif start_command == self.start_game:
                self.game.prepare_for_the_game()
                print(f"Output: {self.game.hidden_sentence} - {self.game.hanged}")
                while True:
                    user_input = input()
                    self.game.play(user_input)
                    state = self.game.check_state()
                    if state is not None:
                        print(state)
                        break
                    print(f"User guess: {user_input}, output changes to: {self.game.hidden_sentence} - {self.game.hanged}")
                break
            elif start_command == self.exit_command:
                break
            else:
                print("Invalid command.")
