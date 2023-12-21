from src.Domain.Book import Book


class BookRentalDaysDTO:
    def __init__(self, book: Book, number_of_rented_books: int):
        self.books = book
        self.number_of_rented_books = number_of_rented_books

    def __str__(self):
        return "Book " + str(self.books) + " has been rented for " + str(self.number_of_rented_books)

    def __repr__(self):
        return str(self)

    @property
    def book(self):
        return self.books

    @property
    def count(self):
        return self.number_of_rented_books
