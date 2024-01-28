import Services
from Error import ServiceError


class UI:
    def __init__(self, services: Services):
        self.service = services

    def start(self):
        while True:
            user_input = input(">")
            command = user_input[:3]
            if command == "add":
                try:
                    self.service.add(user_input)
                except ServiceError as se:
                    print(se)
            command = user_input[:6]
            if command == "create":
                try:
                    self.service.create(user_input)
                except ServiceError as se:
                    print(se)
            command = user_input[:5]
            if command == "start":
                try:
                    quiz = self.service.start(user_input)
                    points = 0
                    for question in quiz:
                        print(f"Question: {question.text}")
                        print(f"First choice: {question.choice1}")
                        print(f"Second choice: {question.choice2}")
                        print(f"Third choice: {question.choice3}", "\n")
                        answer = input("Select your answer: ")
                        if answer == question.correct_answer:
                            print("Correct!", "\n")
                            if question.level == "easy":
                                points += 1
                            elif question.level == "medium":
                                points += 2
                            else:
                                points += 3
                        else:
                            print(f"Wrong! Correct answer: {question.correct_answer}", "\n")
                    print(f"Quiz finished! Final points: {points}")
                except ServiceError as se:
                    print(se)
