from Error import ServiceError
from Repository import Repository


class Services:
    def __init__(self, repo: Repository):
        self.repo = repo

    def add(self, question: str):
        question = question[4:]
        question = question.split(";")
        if not (len(question) == 7):
            raise ServiceError("NOT ENOUGH PARAMETERS.")
        _id, text, choice1, choice2, choice3, correct_answer, level = question[0], question[1], question[2], question[3], question[4], question[5], question[6]
        try:
            _id = int(_id)
        except ValueError:
            raise ServiceError("ID NOT AN INTEGER.")
        if level != "easy":
            raise ServiceError("NOT A CORRECT DIFFICULTY.")
        self.repo.add(_id, text, choice1, choice2, choice3, correct_answer, level)

    def create(self, command: str):
        command = command[7:]
        command = command.split()
        if not (len(command) == 3):
            raise ServiceError("NOT ENOUGH PARAMETERS.")
        difficulty, number_of_questions, file_name = command[0], command[1], command[2]
        if difficulty != "easy" and difficulty != "medium" and difficulty != "hard":
            raise ServiceError("NOT A CORRECT DIFFICULTY.")
        try:
            number_of_questions = int(number_of_questions)
        except ValueError:
            raise ServiceError("NOT AN INTEGER.")
        self.repo.create(difficulty, number_of_questions, file_name)

    def start(self, file_name: str):
        file_name = file_name[6:]
        quiz = self.repo.start(file_name)
        return quiz
