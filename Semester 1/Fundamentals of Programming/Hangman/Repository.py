from Sentences import Sentence


class Repository:
    def __init__(self, file_name: str = "sentences.txt"):
        self.memory = []
        self.file = file_name
        self.read_file()

    def add(self, proposition):
        self.memory.append(Sentence(proposition))

    def read_file(self):
        with open(self.file, "r") as file:
            for line in file.readlines():
                self.memory.append(Sentence(line.strip("\n")))
