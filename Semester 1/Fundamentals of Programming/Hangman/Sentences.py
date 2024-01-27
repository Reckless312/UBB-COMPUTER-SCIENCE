class Sentence:
    def __init__(self, proposition: str):
        self.__proposition = proposition

    @property
    def get_proposition(self):
        return self.__proposition
