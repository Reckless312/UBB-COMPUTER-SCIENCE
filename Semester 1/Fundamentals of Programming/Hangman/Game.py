
from Repository import Repository
from random import choice


class Game:
    def __init__(self, repo: Repository):
        """
        storage = repo
        sentence - str
        hidden_sentence - str
        hanged - str
        :param repo: overload storage
        """
        self.storage = repo
        self.sentence = None
        self.hidden_sentence = None
        self.hanged = ""

    def prepare_for_the_game(self):
        """
        Prepares the sentences for the game
        :return: None
        """
        self.sentence = choice(self.storage.memory)
        self.sentence = self.sentence.get_proposition
        self.hidden_sentence = self.sentence
        self.hidden_sentence = list(self.hidden_sentence)
        for i in range(len(self.hidden_sentence)):
            if self.hidden_sentence[i] != " ":
                self.hidden_sentence[i] = "_"
        self.hidden_sentence = "".join(self.hidden_sentence)
        self.hidden_sentence = list(self.hidden_sentence)
        first_letter, last_letter = self.sentence[0], self.sentence[-1]
        for i in range(len(self.hidden_sentence)):
            if self.sentence[i] == first_letter:
                self.hidden_sentence[i] = first_letter
            elif self.sentence[i] == last_letter:
                self.hidden_sentence[i] = last_letter
        self.hidden_sentence = "".join(self.hidden_sentence)

    def play(self, letter: str):
        """
        Makes a move on the "sentences"
        :param letter: str
        :return: None
        """
        if letter not in self.sentence or letter in self.hidden_sentence:
            hangman = "hangman"
            hangman = list(hangman)
            for i in range(len(hangman)):
                if len(self.hanged) == i:
                    self.hanged = self.hanged + hangman[i]
                    return
        self.hidden_sentence = list(self.hidden_sentence)
        for i in range(len(self.hidden_sentence)):
            if self.sentence[i] == letter:
                self.hidden_sentence[i] = letter
        self.hidden_sentence = "".join(self.hidden_sentence)

    def check_state(self):
        """
        Checks final state
        :return: str / None
        """
        message = None
        if self.hidden_sentence == self.sentence:
            message = "Player won"
            return message
        elif self.hanged == "hangman":
            message = "You lost!"
            return message
