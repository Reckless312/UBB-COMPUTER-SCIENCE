from src.repository import Repository
import pickle

class BinaryFileRepository(Repository):
    def __init__(self, file_name: str = "binary.bin"):
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
            file = open(self.file, "rb")
            self.storage_of_complex_numbers = pickle.load(file)
            self.undo_stack.append(list(self.storage_of_complex_numbers))
            file.close()
        except FileNotFoundError:
            print("NO FILE TO OPEN!")

    def save_file(self):
        """
        Overwrites the repository
        :return: None
        """
        file = open(self.file, "wb")
        pickle.dump(self.storage_of_complex_numbers, file)
        file.close()