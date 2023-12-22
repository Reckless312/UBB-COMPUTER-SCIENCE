from src.BinaryFileRepositories.BinaryFileBookRepository import BinaryFileBookRepository
from src.Domain.Book import import_20_books
from src.DomainRepositories.BookRepository import BookRepository
from src.DomainServices.Command import Command
from src.DomainServices.UndoRedo import UndoRedoService, Operation
from src.Errors.ServicesError import ServicesError
from src.TextFileRepositories.TextFileBookRepository import TextFileBookRepository


class BookServices:
    def __init__(self):
        self.repository = BookRepository()
        self.undo_service = UndoRedoService()

    rental_services = None

    def add(self, _id, title, author):
        try:
            _id = int(_id)
        except ValueError:
            raise ServicesError("Not an integer.")
        if self.find_by_id(_id) is not None:
            raise ServicesError("Object already exists.")
        redo = Command(self.repository.add, self.repository.create_book(_id, title, author))
        undo = Command(self.repository.remove, _id)
        self.repository.add(self.repository.create_book(_id, title, author))
        if isinstance(self.repository, TextFileBookRepository):
            self.repository.save_text_file()
        if isinstance(self.repository, BinaryFileBookRepository):
            self.repository.save_binary_file()
        self.undo_service.register(Operation(undo, redo))

    def do_commands(self, commands):
        for command in commands:
            command()

    def remove(self, _id):
        try:
            _id = int(_id)
        except ValueError:
            raise ServicesError("Not an integer.")
        if self.find_by_id(_id) is None:
            raise ServicesError("Object doesn't exist.")
        old_rental = self.rental_services.get_rental_id_from_book(_id)
        if old_rental is not None:
            undo_commands = [Command(self.repository.add, self.repository.create_book(_id, self.find_by_id(_id).title, self.find_by_id(_id).author)), Command(self.rental_services.was_book_rented, _id), Command(self.rental_services.repository.add, self.rental_services.repository.create_rental(self.rental_services.rent - 1, old_rental.book, old_rental.client, old_rental.start_date, old_rental.end_date))]
            undo = Command(self.do_commands, undo_commands)
            redo_commands = [Command(self.repository.remove, _id), Command(self.rental_services.was_book_rented, _id)]
            redo = Command(self.do_commands, redo_commands)
            self.repository.remove(_id)
            self.rental_services.repository.remove(_id)
            self.undo_service.register(Operation(undo, redo))
        else:
            undo = Command(self.repository.add, self.repository.create_book(_id, self.find_by_id(_id).title, self.find_by_id(_id).author))
            redo = Command(self.repository.remove, _id)
            self.repository.remove(_id)
            self.undo_service.register(Operation(undo, redo))
        if isinstance(self.repository, TextFileBookRepository):
            self.repository.save_text_file()
        if isinstance(self.repository, BinaryFileBookRepository):
            self.repository.save_binary_file()

    def update(self, _id, title, author):
        try:
            _id = int(_id)
        except ValueError:
            raise ServicesError("Not an integer.")
        if _id not in self.repository.data.keys():
            raise ServicesError("Object doesn't exist.")
        old_rental = self.rental_services.get_rental_id_from_book(_id)
        old_book = self.find_by_id(_id)
        old_title, old_author = str(old_book.title), str(old_book.author)
        if old_rental is not None:
            undo_commands = [Command(self.repository.update, (self.repository.change_book(old_book, old_title, old_author))), Command(self.rental_services.repository.update, self.rental_services.repository.change_rental_book(old_rental, old_title, old_author))]
            undo = Command(self.do_commands, undo_commands)
            redo_commands = [Command(self.repository.update, (self.repository.change_book(old_book, title, author))), Command(self.rental_services.repository.update, self.rental_services.repository.change_rental_book(old_rental, title, author))]
            redo = Command(self.do_commands, redo_commands)
            self.repository.update(self.repository.change_book(self.find_by_id(_id), title, author))
            self.undo_service.register(Operation(undo, redo))
        else:
            undo = Command(self.repository.update, (self.repository.change_book(old_book, old_title, old_author)))
            redo = Command(self.repository.update, (self.repository.change_book(old_book, title, author)))
            self.repository.update(self.repository.change_book(self.find_by_id(_id), title, author))
            self.undo_service.register(Operation(undo, redo))
        if isinstance(self.repository, TextFileBookRepository):
            self.repository.save_text_file()
        if isinstance(self.repository, BinaryFileBookRepository):
            self.repository.save_binary_file()

    def list_to_screen(self):
        return self.repository.list()

    def find_by_id(self, _id: int):
        return self.repository.data[_id] if _id in self.repository.data.keys() else None

    def generate_books(self):
        books = import_20_books()
        for one_book in books:
            self.repository.add(self.repository.create_book(one_book.id, one_book.title, one_book.author))

    def find_title(self, book_title):
        books, empty = [], 0
        for a_book in self.repository.data.values():
            if a_book.title.lower() == book_title.lower() or book_title.lower() in a_book.title.lower():
                books.append(a_book)
        if len(books) == empty:
            raise ServicesError("Not found.")
        return books

    def find_author(self, book_author):
        books, empty = [], 0
        for a_book in self.repository.data.values():
            if a_book.author.lower() == book_author.lower() or book_author.lower() in a_book.author.lower():
                books.append(a_book)
        if len(books) == empty:
            raise ServicesError("Not found.")
        return books


if __name__ == "__main__":
    pass
