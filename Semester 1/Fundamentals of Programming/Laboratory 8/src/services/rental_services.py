from datetime import datetime, timedelta
from random import randint
from src.domain.book import Book
from src.domain.client import Client
from src.repository.memory_repository import RepositoryError
from src.repository.rental_repository import RentalRepository


class AuthorRentalDaysDTO:
    def __init__(self, book: Book, number_of_rented_books: int):
        self.author = book.author
        self.number_of_rented_books = number_of_rented_books

    def __str__(self):
        return "Author has been rented for " + str(self.number_of_rented_books) + ", author is " + str(self.author)

    def __repr__(self):
        return str(self)

    @property
    def authors(self):
        return self.author

    @property
    def count(self):
        return self.number_of_rented_books


class ClientRentalDaysDTO:
    def __init__(self, client: Client, day_count: int):
        self.client = client
        self.days = day_count

    def __str__(self):
        return "Active client has rented books for " + str(self.day_count) + ", client " + str(self.client)

    def __repr__(self):
        return str(self)

    def __lt__(self, other):
        return self.day_count <= other.day_count

    @property
    def clients(self):
        return self.client

    @property
    def day_count(self):
        return self.days


class BookRentalDaysDTO:
    def __init__(self, book: Book, number_of_rented_books: int):
        self.books = book
        self.number_of_rented_books = number_of_rented_books

    def __str__(self):
        return "Rented for " + str(self.number_of_rented_books) + ", book is " + str(self.books)

    def __repr__(self):
        return str(self)

    @property
    def book(self):
        return self.books

    @property
    def count(self):
        return self.number_of_rented_books


class RentalServices:
    def __init__(self, books, clients):
        self.books_repo = books
        self.clients_repo = clients
        self.repository = RentalRepository()
        self.repository.generate_20_rentals()
        self.day = datetime(2023, randint(1, 12), randint(1, 28), hour=randint(8, 20))
        self.rent = 21

    def list_to_screen(self):
        return self.repository.list()

    def rent_book(self, book_id, client_id):
        book_id, client_id = self.check_id(book_id), self.check_id(client_id)
        book, client = self.books_repo.find_by_id(book_id), self.clients_repo.find_by_id(client_id)
        if book is not None:
            book.number_of_rents += 1
            self.repository.check_book(book.id)
            self.repository.add(self.repository.create_rental(self.rent, book, client, self.day, self.day + timedelta(days=randint(1, 31))))
            self.rent, self.day = self.rent + 1, self.day + timedelta(days=randint(1, 31))
        else:
            raise RepositoryError("Not a book.")

    def return_book(self, _id):
        _id = self.check_id(_id)
        self.repository.remove(_id)

    def most_books_rented(self):
        """
        Gets and sorts the books by the number of rents
        :return: list
        """
        books = []
        for book in self.books_repo:
            books.append(book)
        number_of_rented_books = {}
        for book in books:
            book_id = book.id
            number_of_rented_books[book_id] = book.number_of_rents
        result = []
        for book in books:
            book_id = book.id
            item = BookRentalDaysDTO(self.books_repo[book_id], number_of_rented_books[book_id])
            result.append(item)
        result.sort(key=lambda x: x.book.get_rent_number, reverse=True)
        return result

    def clients_with_most_rentals(self):
        """
        Gets and sorts clients by the number of days of rented books they have
        :return: list
        """
        clients = []
        for client in self.clients_repo:
            clients.append(client)
        active_rentals = []
        for rental in self.repository:
            active_rentals.append(rental)
        clients_rented = {}
        for rental in active_rentals:
            client_id = rental.client.id
            if client_id not in clients_rented:
                clients_rented[client_id] = [rental]
            else:
                clients_rented[client_id].append(rental)
        clients_rented_days = {}
        for client_id in clients_rented:
            clients_rented_days[client_id] = 0
            for rental in clients_rented[client_id]:
                clients_rented_days[client_id] += len(rental)
        result = []
        for client_id in clients_rented_days:
            item = ClientRentalDaysDTO(self.clients_repo[client_id], clients_rented_days[client_id])
            result.append(item)
        result.sort(reverse=True)
        return result

    def most_rented_author(self):
        """
        Gets and sorts the authors by the number of their books being rented
        :return: list
        """
        books = self.most_books_rented()
        authors = []
        for book in books:
            item = AuthorRentalDaysDTO(book.books, book.number_of_rented_books)
            authors.append(item)
        return authors

    @staticmethod
    def check_id(_id):
        """
        Checks if the id is a valid one
        :param _id: representation of object
        :return: TypeError / int
        """
        try:
            _id = int(_id)
            return _id
        except ValueError:
            raise TypeError("Not an integer.")


if __name__ == "__main__":
    pass
