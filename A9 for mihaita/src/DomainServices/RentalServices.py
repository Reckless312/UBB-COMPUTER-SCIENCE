from src.BinaryFileRepositories.BinaryFileRentalRepository import BinaryFileRentalRepository
from src.DTO.AuthorRentalDaysDTO import AuthorRentalDaysDTO
from src.DTO.BookRentalDaysDTO import BookRentalDaysDTO
from src.DTO.ClientRentalDaysDTO import ClientRentalDaysDTO
from src.Domain.Rental import import_20_rentals
from src.DomainRepositories.BookRepository import BookRepository
from src.DomainRepositories.ClientRepository import ClientRepository
from src.DomainRepositories.RentalRepository import RentalRepository
from src.DomainServices.Command import Command
from src.DomainServices.UndoRedo import UndoRedoService, Operation
from src.Errors.ServicesError import ServicesError
from src.TextFileRepositories.TextFileRentalRepository import TextFileRentalRepository


class RentalServices:
    def __init__(self, books: BookRepository, clients: ClientRepository):
        self.books_repository = books
        self.clients_repository = clients
        self.repository = RentalRepository()
        self.rent = 21
        self.undo_service = UndoRedoService()

    def add(self, _id, book, client, rent_start_date, rent_return_date):
        try:
            _id = int(_id)
        except ValueError:
            raise ServicesError("Not an integer.")
        if self.find_by_id_rental(_id) is not None:
            raise ServicesError("Object already exists.")
        if rent_start_date > rent_return_date:
            raise ServicesError("Days not valid.")
        self.repository.add(self.repository.create_rental(_id, book, client, rent_start_date, rent_return_date))
        if isinstance(self.repository, TextFileRentalRepository):
            self.repository.save_text_file()
        if isinstance(self.repository, BinaryFileRentalRepository):
            self.repository.save_binary_file()

    def rent_book(self, book_id, client_id, rent_day, return_day):
        try:
            book_id, client_id = int(book_id), int(client_id)
        except ValueError:
            raise ServicesError("Not an integer.")
        book, client = self.find_by_id_book(book_id), self.find_by_id_client(client_id)
        if book is not None:
            book.number_of_rents += 1
            self.check_rented(book.id)
            self.repository.add(self.repository.create_rental(self.rent, book, client, rent_day, return_day))
            self.rent += 1
        else:
            raise ServicesError("Not a book.")
        if isinstance(self.repository, TextFileRentalRepository):
            self.repository.save_text_file()
        if isinstance(self.repository, BinaryFileRentalRepository):
            self.repository.save_binary_file()
        redo = Command(self.repository.add, self.repository.create_rental(self.rent - 1, book, client, rent_day, return_day))
        undo = Command(self.repository.remove, self.rent - 1)
        self.undo_service.register(Operation(undo, redo))

    def return_book(self, _id):
        try:
            _id = int(_id)
        except ValueError:
            raise ServicesError("Not an integer.")
        if self.find_by_id_rental(_id) is None:
            raise ServicesError("Object doesn't exist.")
        old_rental = self.find_by_id_rental(_id)
        self.repository.remove(_id)
        if isinstance(self.repository, TextFileRentalRepository):
            self.repository.save_text_file()
        if isinstance(self.repository, BinaryFileRentalRepository):
            self.repository.save_binary_file()
        redo = Command(self.repository.remove, _id)
        undo = Command(self.repository.add, self.repository.create_rental(old_rental.id, old_rental.book, old_rental.client, old_rental.start_date, old_rental.end_date))
        self.undo_service.register(Operation(undo, redo))

    def list_to_screen(self):
        return self.repository.list()

    def find_by_id_book(self, _id: int):
        return self.books_repository.data[_id] if _id in self.books_repository.data.keys() else None

    def find_by_id_client(self, _id: int):
        return self.clients_repository.data[_id] if _id in self.clients_repository.data.keys() else None

    def find_by_id_rental(self, _id: int):
        return self.repository.data[_id] if _id in self.repository.data.keys() else None

    def generate_rentals(self):
        rentals = import_20_rentals()
        for rental in rentals:
            self.add(rental.id, rental.book, rental.client, rental.start_date, rental.end_date)
            rental.book.number_of_rents += 1

    def most_books_rented(self):
        books = []
        for book in self.books_repository:
            books.append(book)
        number_of_rented_books = {}
        for book in books:
            book_id = book.id
            number_of_rented_books[book_id] = book.number_of_rents
        result = []
        for book in books:
            book_id = book.id
            item = BookRentalDaysDTO(self.books_repository[book_id], number_of_rented_books[book_id])
            result.append(item)
        result.sort(key=lambda x: x.book.rents, reverse=True)
        return result

    def clients_with_most_rentals(self):
        clients = []
        for client in self.clients_repository:
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
            item = ClientRentalDaysDTO(self.clients_repository[client_id], clients_rented_days[client_id])
            result.append(item)
        result.sort(reverse=True)
        return result

    def most_rented_author(self):
        books = self.most_books_rented()
        authors = []
        for book in books:
            item = AuthorRentalDaysDTO(book.books, book.number_of_rented_books)
            authors.append(item)
        return authors

    def check_rented(self, book_id):
        for a_rental in self.repository.data.values():
            if a_rental.book.id == book_id:
                raise ServicesError("Already rented.")

    def get_rental_id_from_book(self, book_id):
        for a_rental in self.repository.data.values():
            if int(a_rental.book.id) == book_id:
                return a_rental
        return None

    def was_book_rented(self, book_id):
        try:
            book_id = int(book_id)
        except ValueError:
            raise ServicesError("Not an integer.")
        was_rented = self.get_rental_id_from_book(book_id)
        if was_rented is not None:
            self.repository.remove(was_rented.id)

    def get_rental_id_from_client(self, client_id):
        found_rentals = []
        for a_rental in self.repository.data.values():
            if int(a_rental.client.id) == client_id:
                found_rentals.append(a_rental)
        return found_rentals

    def did_client_rent(self, client_id):
        try:
            client_id = int(client_id)
        except ValueError:
            raise ServicesError("Not an integer.")
        was_rented = self.get_rental_id_from_client(client_id)
        for a_rental in was_rented:
            self.repository.remove(a_rental.id)


if __name__ == "__main__":
    pass
