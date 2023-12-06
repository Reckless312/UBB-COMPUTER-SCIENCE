from src.MemoryRepository import MemoryRepository
from src.TextFileRepository import TextFileRepository
from src.BinaryFileRepository import BinaryFileRepository
"""
Services connects to all 3 Repository types, we can change the desire type(for simplicity
it's placed here), checks proprieties and call further in the repo to implement the functionalities
"""


class Services:
    def __init__(self):
        """
        No need for any
        """
        pass
    """
    Uncomment to choose the desired reposit + comment generate and load to check the unittest!
    """
    # repository = MemoryRepository()
    repository = TextFileRepository()
    # repository = BinaryFileRepository()
    # repository.generate()
    repository.load_file()

    def add(self, real_part, imaginary_part):
        """
        Calls inside the repo to perform the "addition" of a new complex number
        Also saves the file if we are not in the Memory Repo
        :param real_part: float / int (will be checked)
        :param imaginary_part: float / int (will be checked)
        :return: Changes the repo
        """
        Services.is_a_complex_number(real_part, imaginary_part)
        self.repository.add(real_part, imaginary_part)
        if isinstance(self.repository, TextFileRepository) or isinstance(self.repository, BinaryFileRepository):
            self.repository.save_file()

    def display(self):
        """
        Calls inside the repo to display all numbers
        :return: None
        """
        self.repository.display()

    def filter(self, start, end):
        """
        Calls inside the repo to filter the numbers
        Also checks if the starting and ending positions are valid
        :param start: int / (will be checked)
        :param end: int / (will be checked)
        :return: Changes the repo
        """
        Services.is_number(start), Services.is_number(end)
        start, end = int(start), int(end)
        Services.is_in_numbers(start, end, self.repository)
        self.repository.filter(start, end)

    def undo(self):
        """
        Calls inside the repo to undo the numbers
        :return: Changes list (if possible)
        """
        self.repository.undo()
        if isinstance(self.repository, TextFileRepository) or isinstance(self.repository, BinaryFileRepository):
            self.repository.save_file()

    @staticmethod
    def is_number(variable: str):
        """
        Checks if it can be transformed into a number
        :param variable: str
        :return: None / ValueError
        """
        try:
            int(variable)
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

    @staticmethod
    def is_a_complex_number(real_part, imaginary_part):
        """
        Checks if the two parameters can be changed to float
        :param real_part: str
        :param imaginary_part: str
        :return: Changes from str -> float / ValueError
        """
        try:
            real_part = float(real_part)
            imaginary_part = float(imaginary_part)
        except ValueError as ve:
            raise ValueError("NOT A NUMBER")


if __name__ == "__main__":
    pass
