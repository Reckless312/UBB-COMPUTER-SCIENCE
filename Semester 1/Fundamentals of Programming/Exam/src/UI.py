from src.Errors import GameError, GameOver
from src.Services import Service


class UI:
    def __init__(self, services: Service):
        self.service = services

    def start(self):
        print("Welcome to Snake!")
        while True:
            table = self.service.prepare_to_print()
            print(table)
            user_command = input(">")
            command = user_command[:4]
            if command == "move":
                try:
                    self.service.prepare_move(user_command)
                except GameError as ge:
                    print(ge)
                except GameOver as go:
                    print(go)
                    break
            elif user_command == "up" or user_command == "down" or user_command == "left" or user_command == "right":
                try:
                    self.service.change_direction(user_command)
                except GameError as ge:
                    print(ge)
                except GameOver as go:
                    print(go)
                    break
            else:
                print("INVALID COMMAND.")
