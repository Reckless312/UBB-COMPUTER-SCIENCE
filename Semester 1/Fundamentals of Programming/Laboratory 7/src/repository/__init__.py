import random
from src.domain import ComplexNumber
"""
The Repository class connect to ComplexNumber class
Subclasses: MemoryRepository, TextFileRepository, BinaryFileRepository
"""


class Repository:
    def __init__(self):
        """
        Sets up 2 lists:
        One for work
        Second for keeping track of past solutions
        """
        self.storage_of_complex_numbers = []
        self.undo_stack = []

    def __len__(self):
        """
        Allowing to calculate the length of the compendium
        :return: integer
        """
        return len(self.storage_of_complex_numbers)

    def add(self, real_part, imaginary_number):
        """
        Adds a new number
        :param real_part: float
        :param imaginary_number: float
        :return: Changes list
        """
        self.storage_of_complex_numbers.append(ComplexNumber(real_part, imaginary_number))
        self.undo_stack.append(list(self.storage_of_complex_numbers))

    def display(self):
        """
        Display every number in repo
        :return: None
        """
        for number in self.storage_of_complex_numbers:
            print(number)

    def filter(self, start, end):
        """
        Filters the numbers by 2 positions
        :param start: int
        :param end: int
        :return: Changes list
        """
        filtered_list = []
        for i in range(start, end + 1):
            filtered_list.append(self.storage_of_complex_numbers[i])
        self.storage_of_complex_numbers = list(filtered_list)
        self.undo_stack.append(list(self.storage_of_complex_numbers))

    def undo(self):
        """
        Reverts to the last numbers in repo
        :return: Changes list
        """
        original = 1
        if len(self.undo_stack) != original:
            self.undo_stack.pop()
            self.storage_of_complex_numbers = list(self.undo_stack[-1])
        else:
            raise ValueError("NO MORE UNDOES LEFT!")

    def generate(self):
        """
        Generates 10 new numbers in the repo
        :return: Changes list
        """
        for i in range(0, 10):
            number = ComplexNumber(round(random.uniform(0, 100), 1), round(random.uniform(0, 100), 1))
            self.storage_of_complex_numbers.append(number)
        self.undo_stack.append(list(self.storage_of_complex_numbers[:]))


if __name__ == "__main__":
    pass
