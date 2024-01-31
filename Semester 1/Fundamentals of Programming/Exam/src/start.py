# import configparser
# from texttable import Texttable
# import random
#
#
# class GameError(Exception):
#     pass
#
#
# class GameOver(Exception):
#     pass
#
#
# class Game:
#     def __init__(self, length: int, apples: int):
#         self.apples = apples
#         self.length = length
#         self.space = [""] * (self.length * self.length)
#         self.direction = "up"
#         self.snake_head_position = None
#         self.snake_tails = []
#         self.prepare_board()
#
#     def prepare_board(self):
#         middle_column = self.length // 2
#         middle_row = (self.length // 2) * self.length
#         self.space[middle_row + middle_column] = "*"
#         self.space[middle_row + self.length + middle_column] = "+"
#         self.space[middle_row + self.length * 2 + middle_column] = "+"
#         self.generate_apples(self.apples)
#         self.snake_head_position = (middle_row + middle_column)
#         self.snake_tails.append((middle_row + self.length + middle_column))
#         self.snake_tails.append((middle_row + self.length * 2 + middle_column))
#
#     def generate_apples(self, number_of_apples):
#         i = 1
#         while i <= number_of_apples:
#             a = 0
#             b = self.length * self.length
#             random_number = random.randint(a, b - 1)
#             if self.space[random_number] == "":
#                 found_apple = False
#                 if random_number - self.length >= 0:
#                     if self.space[random_number - self.length] == "a":
#                         found_apple = True
#                 if random_number + self.length < self.length * self.length:
#                     if self.space[random_number + self.length] == "a":
#                         found_apple = True
#                 if (random_number + 1) % self.length != 0:
#                     if self.space[random_number + 1] == "a":
#                         found_apple = True
#                 if (random_number - 1) % self.length != 6:
#                     if self.space[random_number - 1] == "a":
#                         found_apple = True
#                 if found_apple is False:
#                     self.space[random_number] = "a"
#                     i = i + 1
#
#     def go_up(self, x, symbol: str):
#         apple = False
#         if self.space[x - self.length] == "a":
#             apple = True
#         self.game_status(x, x - self.length)
#         self.space[x - self.length] = symbol
#         self.snake_head_position = x - self.length
#         return apple
#
#     def go_down(self, x, symbol: str):
#         apple = False
#         if self.space[x + self.length] == "a":
#             apple = True
#         self.game_status(x, x + self.length)
#         self.space[x + self.length] = symbol
#         self.snake_head_position = x + self.length
#         return apple
#
#     def go_right(self, x, symbol: str):
#         apple = False
#         if self.space[x + 1] == "a":
#             apple = True
#         self.game_status(x, x + 1)
#         self.space[x + 1] = symbol
#         self.snake_head_position = x + 1
#         return apple
#
#     def go_left(self, x, symbol: str):
#         apple = False
#         if self.space[x - 1] == "a":
#             apple = True
#         self.game_status(x, x - 1)
#         self.space[x - 1] = symbol
#         self.snake_head_position = x - 1
#         return apple
#
#     def change_tails(self, head_position):
#         save_position = None
#         for i in range(len(self.snake_tails)):
#             save_position = self.snake_tails[i]
#             self.snake_tails[i] = head_position
#             self.space[self.snake_tails[i]] = "+"
#             head_position = save_position
#         self.space[save_position] = ""
#         return save_position
#
#     def __str__(self):
#         table = Texttable()
#         row = 0
#         final_row = self.length * self.length
#         for index in range(row, final_row, self.length):
#             table.add_row(self.space[index:index + self.length])
#         return table.draw()
#
#     def make_move(self, number):
#         for i in range(number):
#             if self.direction == "up":
#                 last_position = self.change_tails(self.snake_head_position)
#                 found_apple = self.go_up(self.snake_head_position, "*")
#                 if found_apple is True:
#                     self.space[last_position] = "+"
#                     self.snake_tails.append(last_position)
#                     self.generate_apples(1)
#             if self.direction == "down":
#                 last_position = self.change_tails(self.snake_head_position)
#                 found_apple = self.go_down(self.snake_head_position, "*")
#                 if found_apple is True:
#                     self.space[last_position] = "+"
#                     self.snake_tails.append(last_position)
#                     self.generate_apples(1)
#             if self.direction == "right":
#                 last_position = self.change_tails(self.snake_head_position)
#                 found_apple = self.go_right(self.snake_head_position, "*")
#                 if found_apple is True:
#                     self.space[last_position] = "+"
#                     self.snake_tails.append(last_position)
#                     self.generate_apples(1)
#             if self.direction == "left":
#                 last_position = self.change_tails(self.snake_head_position)
#                 found_apple = self.go_left(self.snake_head_position, "*")
#                 if found_apple is True:
#                     self.space[last_position] = "+"
#                     self.snake_tails.append(last_position)
#                     self.generate_apples(1)
#
#     def change_direction(self, direction: str):
#         self.direction = direction
#
#     def game_status(self, position, final_position):
#         if self.direction == "up":
#             if (position - self.length) < 0:
#                 raise GameOver("OUTSIDE BOUNDS!")
#         if self.direction == "down":
#             if position + self.length >= self.length * self.length:
#                 raise GameOver("OUTSIDE BOUNDS!")
#         if self.direction == "right":
#             if (position + 1) % self.length == 0:
#                 raise GameOver("OUTSIDE BOUNDS!")
#         if self.direction == "left":
#             if (position - 1) % self.length == 6:
#                 raise GameOver("OUTSIDE BOUNDS!")
#         if self.space[final_position] == "+":
#             raise GameOver("YOU HIT YOURSELF!")
#
#
# class Service:
#     def __init__(self, snake: Game):
#         self.game = snake
#
#     def prepare_move(self, user_input: str):
#         move = user_input[5:]
#         if move == "":
#             move = 1
#         try:
#             move = int(move)
#         except ValueError:
#             raise GameError("Not an integer!")
#         self.game.make_move(move)
#
#     def change_direction(self, user_input: str):
#         directions = ["up", "right", "down", "left"]
#         if user_input not in directions:
#             raise GameError("Not a direction!")
#         current_direction = self.game.direction
#         if current_direction == "up" and user_input == "down":
#             raise GameError("180 direction.")
#         elif current_direction == "right" and user_input == "left":
#             raise GameError("180 direction.")
#         elif current_direction == "left" and user_input == "right":
#             raise GameError("180 direction.")
#         elif current_direction == "down" and user_input == "up":
#             raise GameError("180 direction.")
#         self.game.change_direction(user_input)
#
#
# class UI:
#     def __init__(self, services: Service):
#         self.service = services
#
#     def start(self):
#         print("Welcome to Snake!")
#         while True:
#             print(game)
#             user_command = input(">")
#             command = user_command[:4]
#             if command == "move":
#                 try:
#                     self.service.prepare_move(user_command)
#                 except GameError as ge:
#                     print(ge)
#                 except GameOver as go:
#                     print(go)
#                     break
#             elif user_command == "up" or user_command == "down" or user_command == "left" or user_command == "right":
#                 try:
#                     self.service.change_direction(user_command)
#                 except GameError as ge:
#                     print(ge)
#             else:
#                 print("INVALID COMMAND.")
#
#
# if __name__ == "__main__":
#     config = configparser.RawConfigParser()
#     config.read('settings.properties')
#     N = config.get('Snake', 'N')
#     Apples = config.get('Snake', 'Apples')
#     game = Game(int(N), int(Apples))
#     service = Service(game)
#     ui = UI(service)
#     ui.start()
