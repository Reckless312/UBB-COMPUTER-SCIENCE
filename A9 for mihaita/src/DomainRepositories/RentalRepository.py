from src.Domain.Book import Book
from src.Domain.Client import Client
from src.Domain.Rental import Rental
from src.Repositories.MemoryRepository import MemoryRepository


class RentalRepository(MemoryRepository):
    def __init__(self):
        super().__init__()

    @staticmethod
    def create_rental(rental_id, book, client, rent_date, return_date):
        return Rental(rental_id, book, client, rent_date, return_date)

    @staticmethod
    def change_rental_book(rental: Rental, title, author):
        return Rental(rental.id, RentalRepository.change_book(rental.book, title, author), rental.client, rental.start_date, rental.end_date)

    @staticmethod
    def change_rental_client(rental: Rental, name):
        return Rental(rental.id, rental.book, RentalRepository.change_client(rental.client, name), rental.start_date, rental.end_date)

    @staticmethod
    def change_client(client: Client, name):
        client.name = name
        return Client(client.id, client.name)

    @staticmethod
    def change_book(book: Book, title, author):
        book.title = title
        book.author = author
        return Book(book.id, book.title, book.author)

    @staticmethod
    def create_book(_id, title, author):
        return Book(_id, title, author)

    @staticmethod
    def create_client(_id, name):
        return Client(_id, name)

