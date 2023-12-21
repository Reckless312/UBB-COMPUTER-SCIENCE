from datetime import date, datetime, timedelta
from random import randint

from src.Domain.Book import Book, import_20_books
from src.Domain.Client import Client, import_20_clients
from src.Domain.IdObject import ID


class Rental(ID):
    def __init__(self, _id, book: Book, client: Client, start: date, end: date):
        super().__init__(_id)
        if not isinstance(book, Book):
            raise TypeError("Not a book.")
        if not isinstance(client, Client):
            raise TypeError("Not a client.")
        if not isinstance(start, date) or not isinstance(end, date):
            raise TypeError("Not a date.")
        self.__book = book
        self.__client = client
        self.__start = start
        self.__end = end

    def __str__(self):
        return f"ID: {self.id}\nBook: {self.__book}\nClient: {self.__client}\nStart Date: {self.__start}\nEnd Date: {self.__end}"

    def __len__(self):
        return (self.__end - self.__start).days + 1

    @property
    def book(self):
        return self.__book

    @property
    def client(self):
        return self.__client

    @property
    def start_date(self):
        return self.__start

    @property
    def end_date(self):
        return self.__end


def import_20_rentals():
    """
    Creates 20 hard - coded rentals
    :return: list
    """
    rentals = []
    _id = 1
    books = import_20_books()
    clients = import_20_clients()
    for i in range(20):
        day = datetime(2023, randint(1, 12), randint(1, 28), hour=randint(8, 20))
        rentals.append(Rental(_id, books[i], clients[randint(0, 19)], day, day + timedelta(days=randint(1, 31))))
        _id += 1
    return rentals


if __name__ == "__main__":
    pass
