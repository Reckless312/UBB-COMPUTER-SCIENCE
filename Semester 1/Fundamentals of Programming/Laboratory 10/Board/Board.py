from GameErrors.Errors import BoardError
from texttable import Texttable


class Board:
    def __init__(self):
        self.__columns = 7
        self.__rows = 6
        self.__size = self.__rows * self.__columns
        self.__table = [0] * (self.__columns * self.__rows)
        self.__red_circle = 1
        self.__yellow_circle = -1
        self.__empty_space = 0
        self.__win_score = 4
        self.__validator = [self.__rows - 1] * self.__columns
        self.__move_count = 0

    def make_move(self, column: int, circle_color: str):
        if column < (self.__rows - self.__rows) or column > self.__rows:
            raise BoardError("Outside the board.")
        if self.__validator[column] == -1:
            raise BoardError("Column is full.")
        if circle_color.lower() != "red" and circle_color.lower() != "yellow":
            raise BoardError("Not a corresponding color.")
        if circle_color.lower() == "red":
            self.__table[self.__validator[column] * self.__columns + column] = self.__red_circle
        else:
            self.__table[self.__validator[column] * self.__columns + column] = self.__yellow_circle
        self.__validator[column] -= 1
        self.__move_count += 1

    def final_state(self):
        for row in range(self.__rows):
            score = 0
            for column in range(self.__columns - 3):
                score += self.__table[row * self.__columns + column]
            if abs(score) == self.__win_score:
                return self.__table[row * self.__columns]
            for column in range(self.__columns - 3, self.__columns):
                score -= self.__table[row * self.__columns + (column - 4)]
                score += self.__table[row * self.__columns + column]
                if abs(score) == self.__win_score:
                    return self.__table[row * self.__columns + column]
        for column in range(self.__columns):
            score = 0
            for row in range(self.__rows - 2):
                score += self.__table[row * self.__columns + column]
            if abs(score) == self.__win_score:
                return self.__table[column]
            for row in range(self.__rows - 2, self.__rows):
                score -= self.__table[(row - 4) * self.__columns + column]
                score += self.__table[row * self.__columns + column]
                if abs(score) == self.__win_score:
                    return self.__table[row * self.__columns + column]
        diagonals_in_check, numbers_in_pair = 4, 4
        for column in range(diagonals_in_check):
            score, counter_of_elements, remove_number_position = 0, 0, column
            for diagonal in range(column, self.__size, self.__columns + 1):
                score += self.__table[diagonal]
                counter_of_elements += 1
                if counter_of_elements == numbers_in_pair:
                    if abs(score) == self.__win_score:
                        return self.__table[remove_number_position]
                    score -= self.__table[remove_number_position]
                    remove_number_position += (self.__columns + 1)
                    counter_of_elements -= 1
        to_check, score, diagonal_1, diagonal_2 = 7, 0, 3, 4
        for multiplier in range(5):
            score += self.__table[to_check + (self.__columns + 1) * multiplier]
            if multiplier == diagonal_1 and abs(score) == self.__win_score:
                return self.__table[to_check]
            if multiplier == diagonal_2 and abs(score - self.__table[to_check]) == self.__win_score:
                return self.__table[to_check + (self.__columns + 1)]
        to_check += self.__columns
        if abs(self.__table[to_check] + self.__table[to_check + (self.__columns + 1)] + self.__table[to_check + (self.__columns + 1) * 2] + self.__table[to_check + (self.__columns + 1) * 3]) == self.__win_score:
            return self.__table[to_check]
        start, finish = 3, 7
        for column in range(start, finish):
            score, counter_of_elements, remove_number_position = 0, 0, column
            for diagonal in range(column, self.__size - 1, self.__columns - 1):
                score += self.__table[diagonal]
                counter_of_elements += 1
                if counter_of_elements == numbers_in_pair:
                    if abs(score) == self.__win_score:
                        return self.__table[remove_number_position]
                    score -= self.__table[remove_number_position]
                    remove_number_position += (self.__columns - 1)
                    counter_of_elements -= 1
        to_check, score, diagonal_1, diagonal_2 = 13, 0, 3, 4
        for multiplier in range(5):
            score += self.__table[to_check + (self.__columns - 1) * multiplier]
            if multiplier == diagonal_1 and abs(score) == self.__win_score:
                return self.__table[to_check]
            if multiplier == diagonal_2 and abs(score - self.__table[to_check]) == self.__win_score:
                return self.__table[to_check + (self.__columns - 1)]
        to_check += self.__columns
        if abs(self.__table[to_check] + self.__table[to_check + (self.__columns - 1)] + self.__table[to_check + (self.__columns - 1) * 2] + self.__table[to_check + (self.__columns - 1) * 3]) == self.__win_score:
            return self.__table[to_check]
        return 0

    def is_board_full(self):
        return self.__move_count == self.__size

    def possible_columns(self):
        columns_left = []
        for column in range(self.__columns):
            if self.__validator[column] != -1:
                columns_left.append(column)
        return columns_left

    def create_board(self):
        board = []
        for symbol in self.__table:
            if symbol == self.__empty_space:
                board.append(' ')
            if symbol == self.__red_circle:
                board.append("R")
            if symbol == self.__yellow_circle:
                board.append("Y")
        return board

    def __str__(self):
        display_board = self.create_board()
        table = Texttable()
        row_1, row_2, row_3, row_4, row_5, row_6 = 0, 7, 14, 21, 28, 35
        for index in (row_1, row_2, row_3, row_4, row_5, row_6):
            table.add_row(display_board[index:index + 7])
        return table.draw()

    @property
    def validator(self):
        return self.__validator

    @property
    def table(self):
        return self.__table


if __name__ == "__main__":
    pass
