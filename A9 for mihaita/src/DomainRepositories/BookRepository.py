from src.Domain.Book import Book
from src.Repositories.MemoryRepository import MemoryRepository


class BookRepository(MemoryRepository):
    def __init__(self):
        super().__init__()

    @staticmethod
    def create_book(_id, title, author):
        return Book(_id, title, author)

    @staticmethod
    def change_book(book: Book, title, author):
        book.title = title
        book.author = author
        return Book(book.id, book.title, book.author)
