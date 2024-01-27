from Errors import ServiceError
from Repository import Repository


class Services:
    def __init__(self, repo: Repository):
        self.repository = repo

    def add(self, proposition: str):
        word_checker = proposition.split()
        if len(word_checker) == 0:
            raise ServiceError("NO WORDS IN PROPOSITION.")
        for word in word_checker:
            if len(word) < 3:
                raise ServiceError("LESS THAN 3 WORDS.")
        sentences = self.repository.memory
        for proposition in sentences:
            if proposition.get_proposition == proposition:
                raise ServiceError("SENTENCE ALREADY PRESENT")
        self.repository.add(proposition)
