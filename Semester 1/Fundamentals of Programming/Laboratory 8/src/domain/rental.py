from datetime import date, datetime, timedelta
from random import randint
from src.domain.book import Book, import_20_books
from src.domain.client import Client, import_20_clients
from src.domain.idObject import ID


class Rental(ID):
    """
    Type rental represented by an id, a book, a client, a starting date for rent and an ending one
    """
    def __init__(self, _id, book: Book, client: Client, start: date, end: date):
        super().__init__(_id)
        if not isinstance(book, Book):
            raise TypeError("Not a book.")
        if not isinstance(client, Client):
            raise TypeError("Not a client.")
        if not isinstance(start, date) or not isinstance(end, date):
            raise TypeError("Not a date.")
        self.book = book
        self.client = client
        self.start = start
        self.end = end

    def __str__(self):
        return f'ID: {self.id}\nBook: {self.book}\nClient: {self.client}\nStart Date: {self.start}\nEnd date: {self.end}'

    def __len__(self):
        return (self.end - self.start).days + 1


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
