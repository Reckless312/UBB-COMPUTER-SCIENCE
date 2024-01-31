from random import randint

from texttable import Texttable

from src.Errors import GameOver


class Game:
    def __init__(self, length: int, apples: int):
        self.apples = apples
        self.length = length
        self.space = [""] * (self.length * self.length)
        self.direction = "up"
        self.snake_head_position = None
        self.snake_tails = []
        self.prepare_board()

    def prepare_board(self):
        """
        Places the head of the snake in the board while 2 of his body segments
        :return: None / changes list
        """
        middle_column = self.length // 2
        middle_row = (self.length // 2) * self.length
        self.space[middle_row + middle_column] = "*"
        self.space[middle_row + self.length + middle_column] = "+"
        self.space[middle_row + self.length * 2 + middle_column] = "+"
        self.generate_apples(self.apples)
        self.snake_head_position = (middle_row + middle_column)
        self.snake_tails.append((middle_row + self.length + middle_column))
        self.snake_tails.append((middle_row + self.length * 2 + middle_column))

    def generate_apples(self, number_of_apples):
        """
        Checks for random places where apples can be places and puts them
        :param number_of_apples: how many apple we want
        :return: None / Changes list
        """
        i = 1
        while i <= number_of_apples:
            a = 0
            b = self.length * self.length
            random_number = randint(a, b - 1)
            if self.space[random_number] == "":
                found_apple = False
                if random_number - self.length >= 0:
                    if self.space[random_number - self.length] == "a":
                        found_apple = True
                if random_number + self.length < self.length * self.length:
                    if self.space[random_number + self.length] == "a":
                        found_apple = True
                if (random_number + 1) % self.length != 0:
                    if self.space[random_number + 1] == "a":
                        found_apple = True
                if (random_number - 1) % self.length != 6:
                    if self.space[random_number - 1] == "a":
                        found_apple = True
                if found_apple is False:
                    self.space[random_number] = "a"
                    i = i + 1

    def go_up(self, x, symbol: str):
        """
        A function that helps the snake head move up
        :param x: current position
        :param symbol: *
        :return: bool -> if he ate an apple
        """
        self.game_status(x, x - self.length)
        apple = False
        if self.space[x - self.length] == "a":
            apple = True
        self.space[x - self.length] = symbol
        self.snake_head_position = x - self.length
        return apple

    def go_down(self, x, symbol: str):
        """
        A function that helps the snake head move down
        :param x: current position
        :param symbol: *
        :return: bool -> if he ate an apple
        """
        self.game_status(x, x + self.length)
        apple = False
        if self.space[x + self.length] == "a":
            apple = True
        self.space[x + self.length] = symbol
        self.snake_head_position = x + self.length
        return apple

    def go_right(self, x, symbol: str):
        """
        A function that helps the snake head move right
        :param x: current position
        :param symbol: *
        :return: bool -> if he ate an apple
        """
        self.game_status(x, x + 1)
        apple = False
        if self.space[x + 1] == "a":
            apple = True
        self.space[x + 1] = symbol
        self.snake_head_position = x + 1
        return apple

    def go_left(self, x, symbol: str):
        """
        A function that helps the snake head move left
        :param x: current position
        :param symbol: *
        :return: bool -> if he ate an apple
        """
        self.game_status(x, x - 1)
        apple = False
        if self.space[x - 1] == "a":
            apple = True
        self.space[x - 1] = symbol
        self.snake_head_position = x - 1
        return apple

    def change_tails(self, head_position):
        """
        A function that keeps track of last position of trails and switches them along the head
        :param head_position: where the head is currently placed / later used for keeping the trail positions
        :return: last emptied position
        """
        save_position = None
        for i in range(len(self.snake_tails)):
            save_position = self.snake_tails[i]
            self.snake_tails[i] = head_position
            self.space[self.snake_tails[i]] = "+"
            head_position = save_position
        self.space[save_position] = ""
        return save_position

    def __str__(self):
        table = Texttable()
        row = 0
        final_row = self.length * self.length
        for index in range(row, final_row, self.length):
            table.add_row(self.space[index:index + self.length])
        return table.draw()

    def make_move(self, number):
        """
        Makes a move on the board while trying to keep in mind of all the elements: game over, apples...
        :param number: number of moves
        :return: None / Changes Board
        """
        for i in range(number):
            if self.direction == "up":
                last_position = self.change_tails(self.snake_head_position)
                found_apple = self.go_up(self.snake_head_position, "*")
                if found_apple is True:
                    self.space[last_position] = "+"
                    self.snake_tails.append(last_position)
                    self.generate_apples(1)
            if self.direction == "down":
                last_position = self.change_tails(self.snake_head_position)
                found_apple = self.go_down(self.snake_head_position, "*")
                if found_apple is True:
                    self.space[last_position] = "+"
                    self.snake_tails.append(last_position)
                    self.generate_apples(1)
            if self.direction == "right":
                last_position = self.change_tails(self.snake_head_position)
                found_apple = self.go_right(self.snake_head_position, "*")
                if found_apple is True:
                    self.space[last_position] = "+"
                    self.snake_tails.append(last_position)
                    self.generate_apples(1)
            if self.direction == "left":
                last_position = self.change_tails(self.snake_head_position)
                found_apple = self.go_left(self.snake_head_position, "*")
                if found_apple is True:
                    self.space[last_position] = "+"
                    self.snake_tails.append(last_position)
                    self.generate_apples(1)

    def change_direction(self, direction: str):
        """
        Simply change direction and then makes a move
        :param direction: "up", "left", "right", "down"
        :return: None
        """
        self.direction = direction
        self.make_move(1)

    def game_status(self, position, final_position):
        """
        Checks if the game is over
        :param position: current position
        :param final_position: where the snake end up
        :return: GameOver / None
        """
        if self.direction == "up":
            if (position - self.length) < 0:
                raise GameOver("OUTSIDE BOUNDS!")
        if self.direction == "down":
            if position + self.length >= self.length * self.length:
                raise GameOver("OUTSIDE BOUNDS!")
        if self.direction == "right":
            if (position + 1) % self.length == 0:
                raise GameOver("OUTSIDE BOUNDS!")
        if self.direction == "left":
            if (position - 1) % self.length == 6:
                raise GameOver("OUTSIDE BOUNDS!")
        if self.space[final_position] == "+":
            raise GameOver("YOU HIT YOURSELF!")
