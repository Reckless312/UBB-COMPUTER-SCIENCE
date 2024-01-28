from random import choice

from Error import RepositoryError
from Question import Question
from generate_questions import generate_100_pseudo_random_questions


class Repository:
    def __init__(self):
        self.master_question = []
        self.quiz = []
        self.prepare_questions()

    def prepare_questions(self):
        questions = generate_100_pseudo_random_questions()
        for question in questions:
            question = question.split(";")
            _id = question[0]
            text = question[1]
            choice1 = question[2]
            choice2 = question[3]
            choice3 = question[4]
            correct_answer = question[5]
            level = question[6]
            self.master_question.append(Question(int(_id), text, choice1, choice2, choice3, correct_answer, level))

    def add(self, _id: int, text: str, choice1, choice2, choice3, correct_answer, level):
        self.master_question.append(Question(_id, text, choice1, choice2, choice3, correct_answer, level))

    def create(self, difficulty, number_of_question, file_name):
        easy_questions, medium_questions, hard_questions = [], [], []
        for question in self.master_question:
            if question.level == "easy":
                easy_questions.append(question)
            elif question.level == "medium":
                medium_questions.append(question)
            else:
                hard_questions.append(question)
        with open(file_name, "w") as file:
            i = 1
            while i <= number_of_question:
                if difficulty == "easy":
                    file.write(str(choice(easy_questions)))
                    file.write("\n")
                elif difficulty == "medium":
                    file.write(str(choice(choice([easy_questions, medium_questions]))))
                    file.write("\n")
                else:
                    file.write(str(choice(choice([easy_questions, medium_questions, hard_questions]))))
                    file.write("\n")
                i += 1

    def start(self, file_name):
        try:
            with open(file_name, "r") as file:
                for line in file.readlines():
                    line = line.strip("\n")
                    self.quiz.append(Question(*(line.split(";"))))
        except FileNotFoundError:
            raise RepositoryError("FILE NOT FOUND")
        return self.quiz
