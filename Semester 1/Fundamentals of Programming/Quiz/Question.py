class Question:
    def __init__(self, _id: int, text: str, choice1, choice2, choice3, correct_answer, level):
        self.id = _id
        self.text = text
        self.choice1 = choice1
        self.choice2 = choice2
        self.choice3 = choice3
        self.correct_answer = correct_answer
        self.level = level

    def __str__(self):
        return f"{self.id};{self.text};{self.choice1};{self.choice2};{self.choice3};{self.correct_answer};{self.level}"
