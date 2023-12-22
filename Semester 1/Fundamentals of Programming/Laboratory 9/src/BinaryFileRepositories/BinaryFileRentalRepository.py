import pickle

from src.DomainRepositories.RentalRepository import RentalRepository


class BinaryFileRentalRepository(RentalRepository):
    def __init__(self, file_name: str = "data.bin"):
        super().__init__()
        self.file = file_name

    def load_binary_file(self):
        try:
            file = open(self.file, "rb")
            self.data = pickle.load(file)
            file.close()
        except FileNotFoundError:
            print("NO FILE TO OPEN!")

    def save_binary_file(self):
        file = open(self.file, "wb")
        pickle.dump(self.data, file)
        file.close()
