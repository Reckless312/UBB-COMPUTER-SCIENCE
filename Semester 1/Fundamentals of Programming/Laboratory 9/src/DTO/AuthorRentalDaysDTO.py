from src.Domain.Book import Book


class AuthorRentalDaysDTO:
    def __init__(self, book: Book, number_of_rented_books: int):
        self.author = book.author
        self.number_of_rented_books = number_of_rented_books

    def __str__(self):
        return "Author " + str(self.author) + " has been rented for " + str(self.number_of_rented_books)

    def __repr__(self):
        return str(self)

    @property
    def authors(self):
        return self.author

    @property
    def count(self):
        return self.number_of_rented_books
