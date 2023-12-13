from src.domain.book import Book, import_20_books
from src.repository.memory_repository import MemoryRepository, RepositoryError


class BookRepository(MemoryRepository):
    def __init__(self):
        """
        Subclass of MemoryRepository, inherits all attributes
        """
        super().__init__()

    def generate_books(self):
        """
        Generates 20 books in the repository
        :return: changes the repository
        """
        books = import_20_books()
        for one_book in books:
            self.add(one_book)

    def find_title(self, book_title):
        """
        Find books from a title
        :param book_title: str, the one desired
        :return: A list of all books that are partially related to title inserted
        """
        books, empty = [], 0
        for a_book in self.data.values():
            if a_book.title.lower() == book_title.lower() or book_title.lower() in a_book.title.lower():
                books.append(a_book)
        if len(books) == empty:
            raise RepositoryError("Not found.")
        return books

    def find_author(self, book_author):
        """
        Find books from an author
        :param book_author: str, the one desired
        :return: A list of all books that are partially related to the author inserted
        """
        books, empty = [], 0
        for a_book in self.data.values():
            if a_book.author.lower() == book_author.lower() or book_author.lower() in a_book.author.lower():
                books.append(a_book)
        if len(books) == empty:
            raise RepositoryError("Not found.")
        return books

    @staticmethod
    def create_book(_id, title, author):
        """
        Creates a book
        :param _id: type ID, representation
        :param title: str, name
        :param author: str, name
        :return: Book
        """
        return Book(_id, title, author)
