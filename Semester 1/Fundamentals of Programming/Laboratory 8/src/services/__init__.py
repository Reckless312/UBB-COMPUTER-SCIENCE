from src.domain import ComplexNumber
from src.repository import Repository


class Services:
    def __init__(self, reposit: list, previous_numbers: list):
        """
        Makes the desired commands
        :param reposit: current compendium
        :param previous_numbers: all available compendiums
        """
        self.storage_of_complex_numbers = reposit
        self.undo_stack = previous_numbers

    def add(self, number: ComplexNumber):
        """
        Finishes to append a new number
        :param number: complex number
        :return: None / list changes
        """
        self.storage_of_complex_numbers.append(number)
        self.undo_stack.append(list(self.storage_of_complex_numbers))

    def display(self):
        """
        Displays all numbers
        :return: None
        """
        for number in self.storage_of_complex_numbers:
            print(number)

    def filter(self, start: int, end: int):
        """
        Creates a new list with only the desired numbers
        :param start: position to begin
        :param end: position to end
        :return: Changes in the list
        """
        filtered_list = []
        for i in range(start, end + 1):
            filtered_list.append(self.storage_of_complex_numbers[i])
        self.storage_of_complex_numbers = list(filtered_list)
        self.undo_stack.append(list(self.storage_of_complex_numbers))

    def undo(self):
        """
        Reverts back to past compendium
        :return: Changes list / ValueError
        """
        original = 1
        if len(self.undo_stack) != original:
            self.undo_stack.pop()
            self.storage_of_complex_numbers = list(self.undo_stack[-1])
        else:
            raise ValueError("NO MORE UNDOES LEFT!")

    @property
    def get_data(self):
        """
        Getter
        :return: data
        """
        return self.storage_of_complex_numbers

    @property
    def get_stack(self):
        """
        Getter
        :return: stack
        """
        return self.undo_stack

    @staticmethod
    def is_number(variable: str):
        """
        Checks if it can be transformed into a number
        :param variable: str
        :return: None / ValueError
        """
        try:
            float(variable)
        except ValueError as ve:
            raise ValueError("NOT A NUMBER!")

    @staticmethod
    def is_in_numbers(start: int, end: int, data):
        """
        Checks if the desired positions are in data
        :param start: position to begin
        :param end: position to end
        :param data: data with complex numbers
        :return: None / ValueError
        """
        if start <= end <= len(data) - 1:
            pass
        else:
            raise ValueError("OUT OF BOUNDS!")


if __name__ == "__main__":
    pass
