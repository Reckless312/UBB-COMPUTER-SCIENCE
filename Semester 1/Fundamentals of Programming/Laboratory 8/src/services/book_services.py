from src.repository.book_repository import BookRepository, RepositoryError


class BookServices:
    """
    Knows about BookRepositories and works with it
    """
    def __init__(self):
        self.repository = BookRepository()
        self.repository.generate_books()

    def add(self, _id, title, author):
        _id = self.check_id(_id)
        self.repository.add(self.repository.create_book(_id, title, author))

    def remove(self, _id):
        _id = self.check_id(_id)
        self.repository.remove(_id)

    def update(self, _id, title, author):
        _id = self.check_id(_id)
        self.repository.update(self.repository.create_book(_id, title, author))

    def list_to_screen(self):
        return self.repository.list()

    def search_with_id(self, _id):
        _id = self.check_id(_id)
        return self.repository.find_by_id(_id)

    def search_with_title(self, title):
        return self.repository.find_title(title)

    def search_with_author(self, author):
        return self.repository.find_author(author)

    @staticmethod
    def check_id(_id):
        """
        Checks if the id is a valid one
        :param _id: representation of object
        :return: RepositoryError / int
        """
        try:
            _id = int(_id)
            return _id
        except ValueError:
            raise RepositoryError("Not an integer.")


if __name__ == "__main__":
    pass
