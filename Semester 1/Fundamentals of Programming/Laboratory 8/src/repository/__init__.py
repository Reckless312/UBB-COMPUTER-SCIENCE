import random


class Repository:
    def __init__(self):
        """
        Sets up 2 lists:
        One for work
        Second for keeping track of past solutions
        """
        self.storage_of_complex_numbers = []
        self.undo_stack = []

    def add(self, number: ComplexNumber):
        """
        Adds to the memory a new number
        :param number: complex number
        :return: append to data
        """
        instructions = Services(self.storage_of_complex_numbers, self.undo_stack)
        instructions.add(number)
        self.storage_of_complex_numbers = list(instructions.get_data)
        self.undo_stack = list(instructions.get_stack)

    def display(self):
        """
        Displays all numbers
        :return: None
        """
        instructions = Services(self.storage_of_complex_numbers, self.undo_stack)
        instructions.display()

    def filter(self, start: int, end: int):
        """
        Filters the list from 2 positions
        :param start: start of the interval
        :param end: end of the interval
        :return: shorted list
        """
        instructions = Services(self.storage_of_complex_numbers, self.undo_stack)
        instructions.filter(start, end)
        self.storage_of_complex_numbers = list(instructions.get_data)
        self.undo_stack = list(instructions.get_stack)

    def undo(self):
        """
        Reverts to past solution
        :return: previous list
        """
        instructions = Services(self.storage_of_complex_numbers, self.undo_stack)
        instructions.undo()
        self.storage_of_complex_numbers = list(instructions.get_data)
        self.undo_stack = list(instructions.get_stack)

    def generate(self):
        """
        Generates 10 random complex numbers
        :return: appends 10 numbers to the data
        """
        for i in range(0, 10):
            number = ComplexNumber(round(random.uniform(0, 100), 1), round(random.uniform(0, 100), 1))
            self.storage_of_complex_numbers.append(number)
        self.undo_stack.append(list(self.storage_of_complex_numbers[:]))

    def __len__(self):
        """
        Allowing to calculate the length of the compendium
        :return: integer
        """
        return len(self.storage_of_complex_numbers)


if __name__ == "__main__":
    pass
