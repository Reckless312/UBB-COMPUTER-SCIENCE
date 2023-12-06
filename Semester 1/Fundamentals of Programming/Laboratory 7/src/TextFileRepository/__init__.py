from src.repository import Repository
"""
Doesn't connect with any other package
"""


class TextFileRepository(Repository):
    """
    Subclass of Repository
    """
    def __init__(self, file_name: str = "data.bin"):
        """
        Repository + file_name
        :param file_name: Normal txt file
        """
        super().__init__()
        self.file = file_name

    def load_file(self):
        """
        Reads from file.txt
        :return: Changes list / FileNotFound Error
        """
        try:
            file = open(self.file, "r")
            for line in file:
                number = line[:-1].split()
                real_part, imaginary_part = 0, 2
                self.add(float(number[real_part]), float(number[imaginary_part]))
            self.undo_stack.append(list(self.storage_of_complex_numbers))
            file.close()
        except FileNotFoundError:
            print("NO FILE TO OPEN!")

    def save_file(self):
        """
        Overwrites the repository
        :return: None
        """
        file = open(self.file, "w")
        for number in self.storage_of_complex_numbers:
            file.write("%s\n" % number)
        file.close()
