from datetime import datetime

from src.DomainServices.BookServices import BookServices
from src.DomainServices.ClientServices import ClientServices
from src.DomainServices.RentalServices import RentalServices
from src.Errors.RepositoryError import RepositoryError
from src.Errors.ServicesError import ServicesError
from src.Errors.UndoRedoError import UndoRedoError


class UI:
    def __init__(self):
        self.book = BookServices()
        self.client = ClientServices()
        self.rental = RentalServices(self.book.repository, self.client.repository)
        self.book.rental_services = self.rental
        self.client.rental_services = self.rental

    def start(self):
        print("Starting program...")
        command_manage, command_rent, command_search, command_statistics, command_exit = "1", "2", "3", "4", "0"
        while True:
            self.print_main_menu(command_manage, command_rent, command_search, command_statistics, command_exit)
            menu_command = input(">")
            if menu_command == command_manage:
                self.start_manage()
            elif menu_command == command_rent:
                pass
                self.start_rent()
            elif menu_command == command_search:
                pass
                self.start_search()
            elif menu_command == command_statistics:
                pass
                self.start_statistics()
            elif menu_command == command_exit:
                break
            else:
                print("Invalid command.")

    def start_manage(self):
        command_add, command_remove, command_update, command_list, command_undo, command_redo, command_exit = "1", "2", "3", "4", "5", "6", "0"
        command_book, command_client, command_back = "1", "2", "0"
        while True:
            self.print_manage_menu(command_add, command_remove, command_update, command_list, command_undo, command_redo, command_exit)
            menu_managing_command = input(">")
            if menu_managing_command == command_add:
                self.print_available_objects(command_book, command_client, command_back)
                managing_object_command = input(">")
                if managing_object_command == command_book:
                    try:
                        _id, title, author = input("Insert id: "), input("Insert title: "), input("Insert author: ")
                        self.book.add(_id, title, author)
                    except RepositoryError as re:
                        print(re)
                    except ServicesError as se:
                        print(se)
                    except TypeError as te:
                        print(te)
                elif managing_object_command == command_client:
                    try:
                        _id, client_name = input("Insert id: "), input("Insert client: ")
                        self.client.add(_id, client_name)
                    except RepositoryError as re:
                        print(re)
                    except ServicesError as se:
                        print(se)
                    except TypeError as te:
                        print(te)
                elif managing_object_command == command_back:
                    pass
                else:
                    print("Invalid command.")
            elif menu_managing_command == command_remove:
                self.print_remove_commands(command_book, command_client, command_back)
                remove_command = input(">")
                if remove_command == command_book:
                    try:
                        remove_id = input("Id to be deleted: ")
                        self.book.remove(remove_id)
                    except RepositoryError as re:
                        print(re)
                    except ServicesError as se:
                        print(se)
                    except TypeError as te:
                        print(te)
                elif remove_command == command_client:
                    try:
                        remove_id = input("Id to be deleted: ")
                        self.client.remove(remove_id)
                    except RepositoryError as re:
                        print(re)
                    except ServicesError as se:
                        print(se)
                    except TypeError as te:
                        print(te)
                elif remove_command == command_back:
                    pass
                else:
                    print("Invalid command.")
            elif menu_managing_command == command_update:
                self.print_update_commands(command_book, command_client, command_back)
                update_command = input(">")
                if update_command == command_book:
                    try:
                        _id, title, author = input("Insert id: "), input("Insert new title: "), input("Insert new author: ")
                        self.book.update(_id, title, author)
                    except RepositoryError as re:
                        print(re)
                    except ServicesError as se:
                        print(se)
                    except TypeError as te:
                        print(te)
                elif update_command == command_client:
                    try:
                        _id, client_name = input("Insert id: "), input("Insert new client name: ")
                        self.client.update(_id, client_name)
                    except RepositoryError as re:
                        print(re)
                    except ServicesError as se:
                        print(se)
                    except TypeError as te:
                        print(te)
                elif update_command == command_back:
                    pass
                else:
                    print("Invalid command.")
            elif menu_managing_command == command_list:
                self.print_available_objects(command_book, command_client, command_back)
                managing_object_command = input(">")
                if managing_object_command == command_book:
                    books = self.book.list_to_screen()
                    for book in books:
                        print(book)
                elif managing_object_command == command_client:
                    clients = self.client.list_to_screen()
                    for client in clients:
                        print(client)
                elif managing_object_command == command_back:
                    pass
                else:
                    print("Invalid command.")
            elif menu_managing_command == command_undo:
                self.print_undo_menu(command_book, command_client, command_back)
                undo_command = input(">")
                if undo_command == command_book:
                    try:
                        self.book.undo_service.undo()
                    except UndoRedoError as ure:
                        print(ure)
                elif undo_command == command_client:
                    try:
                        self.client.undo_service.undo()
                    except UndoRedoError as ure:
                        print(ure)
                elif undo_command == command_back:
                    pass
                else:
                    print("Invalid command.")
            elif menu_managing_command == command_redo:
                self.print_redo_menu(command_book, command_client, command_back)
                redo_command = input(">")
                if redo_command == command_book:
                    try:
                        self.book.undo_service.redo()
                    except UndoRedoError as ure:
                        print(ure)
                elif redo_command == command_client:
                    try:
                        self.client.undo_service.redo()
                    except UndoRedoError as ure:
                        print(ure)
                elif redo_command == command_back:
                    pass
                else:
                    print("Invalid command.")
            elif menu_managing_command == command_exit:
                break
            else:
                print("Invalid command.")

    def start_rent(self):
        command_rent, command_return, command_list, command_undo, command_redo, command_back = "1", "2", "3", "4", "5", "0"
        while True:
            self.print_menu_rent(command_rent, command_return, command_list, command_undo, command_redo, command_back)
            rental_command = input(">")
            if rental_command == command_rent:
                try:
                    book_id, client_id = input("Select the id of a book: "), input("Select your id: ")
                    start_date, end_date = input("Select the day you wish to rent the book: "), input("Select the day of the return: ")
                    date_format = "%Y-%m-%d"
                    start_date, end_date = datetime.strptime(start_date, date_format), datetime.strptime(end_date, date_format)
                    self.rental.rent_book(book_id, client_id, start_date, end_date)
                except RepositoryError as re:
                    print(re)
                except ServicesError as se:
                    print(se)
                except TypeError as te:
                    print(te)
                except ValueError as ve:
                    print(ve)
            elif rental_command == command_return:
                try:
                    rental_id = input("Select the rental id: ")
                    self.rental.return_book(rental_id)
                except RepositoryError as re:
                    print(re)
                except ServicesError as se:
                    print(se)
                except TypeError as te:
                    print(te)
            elif rental_command == command_list:
                rentals = self.rental.list_to_screen()
                for rental in rentals:
                    print(rental)
            elif rental_command == command_undo:
                try:
                    self.rental.undo_service.undo()
                except UndoRedoError as ure:
                    print(ure)
            elif rental_command == command_redo:
                try:
                    self.rental.undo_service.redo()
                except UndoRedoError as ure:
                    print(ure)
            elif rental_command == command_back:
                break
            else:
                print("Invalid command.")

    def start_search(self):
        command_book, command_client, command_back = "1", "2", "0"
        command_id, command_title, command_name, command_author, command_cancel = "1", "2", "2", "3", "0"
        while True:
            self.print_search_commands(command_book, command_client, command_back)
            search_command = input(">")
            if search_command == command_book:
                self.print_search_books_commands(command_id, command_title, command_author, command_cancel)
                search_attribute = input(">")
                if search_attribute == command_id:
                    try:
                        _id = input("Insert id: ")
                        book = self.book.find_by_id(int(_id))
                        print(book)
                    except RepositoryError as re:
                        print(re)
                    except ServicesError as se:
                        print(se)
                    except TypeError as te:
                        print(te)
                    except ValueError:
                        print("Not an integer.")
                elif search_attribute == command_title:
                    try:
                        title = input("Insert title: ")
                        books = self.book.find_title(title)
                        for book in books:
                            print(book)
                    except RepositoryError as re:
                        print(re)
                    except ServicesError as se:
                        print(se)
                    except TypeError as te:
                        print(te)
                elif search_attribute == command_author:
                    try:
                        author = input("Insert author: ")
                        books = self.book.find_author(author)
                        for book in books:
                            print(book)
                    except RepositoryError as re:
                        print(re)
                    except ServicesError as se:
                        print(se)
                    except TypeError as te:
                        print(te)
                elif search_attribute == command_cancel:
                    pass
                else:
                    print("Invalid command.")
            elif search_command == command_client:
                self.print_search_client_commands(command_id, command_name, command_cancel)
                search_attribute = input(">")
                if search_attribute == command_id:
                    try:
                        _id = input("Insert id: ")
                        client = self.client.find_by_id(int(_id))
                        print(client)
                    except RepositoryError as re:
                        print(re)
                    except ServicesError as se:
                        print(se)
                    except TypeError as te:
                        print(te)
                    except ValueError:
                        print("Not an integer.")
                elif search_attribute == command_name:
                    try:
                        client_name = input("Insert name: ")
                        clients = self.client.find_name(client_name)
                        for client in clients:
                            print(client)
                    except RepositoryError as re:
                        print(re)
                    except ServicesError as se:
                        print(se)
                    except TypeError as te:
                        print(te)
                elif search_attribute == command_cancel:
                    pass
                else:
                    print("Invalid command.")
            elif search_command == command_back:
                break
            else:
                print("Invalid command.")

    def start_statistics(self):
        command_book, command_client, command_author, command_back = "1", "2", "3", "0"
        while True:
            self.print_menu_statistics(command_book, command_client, command_author, command_back)
            statistics_command = input(">")
            if statistics_command == command_book:
                try:
                    books = self.rental.most_books_rented()
                    for book in books:
                        print(book)
                except RepositoryError as re:
                    print(re)
                except ServicesError as se:
                    print(se)
                except TypeError as te:
                    print(te)
            elif statistics_command == command_client:
                try:
                    clients = self.rental.clients_with_most_rentals()
                    for client in clients:
                        print(client)
                except RepositoryError as re:
                    print(re)
                except ServicesError as se:
                    print(se)
                except TypeError as te:
                    print(te)
            elif statistics_command == command_author:
                authors = self.rental.most_rented_author()
                for author in authors:
                    print(author)
            elif statistics_command == command_back:
                break
            else:
                print("Invalid command.")

    @staticmethod
    def print_manage_menu(command_add: str, command_remove: str, command_update: str, command_list: str, command_undo: str, command_redo: str, command_back: str):
        print("Select the managing method:")
        print(f"\tAdd a new object / {command_add}.")
        print(f"\tRemove one object / {command_remove}.")
        print(f"\tUpdate an object / {command_update}.")
        print(f"\tShow on screen an object / {command_list}.")
        print(f"\tUndo operation / {command_undo}.")
        print(f"\tRedo operation / {command_redo}.")
        print(f"\tGo back / {command_back}.")

    @staticmethod
    def print_available_objects(command_book: str, command_client: str, command_back: str):
        print("Select desired object:")
        print(f"\tBook / {command_book}.")
        print(f"\tClient / {command_client}.")
        print(f"\tGo back / {command_back}.")

    @staticmethod
    def print_remove_commands(command_book: str, command_client: str, command_back: str):
        print("What do you want to remove?")
        print(f"\tRemove a book / {command_book}.")
        print(f"\tRemove a client / {command_client}.")
        print(f"\tGo back / {command_back}.")

    @staticmethod
    def print_update_commands(command_book: str, command_client: str, command_back: str):
        print("What do you want to update?")
        print(f"\tUpdate a book / {command_book}.")
        print(f"\tUpdate a client / {command_client}.")
        print(f"\tGo back / {command_back}.")

    @staticmethod
    def print_main_menu(command_manage: str, command_rent: str, command_search: str, command_statistics: str, command_exit: str):
        print("Select the desired command:")
        print(f"\tManage clients and books / {command_manage}.")
        print(f"\tRental books / {command_rent}.")
        print(f"\tSearch with criteria / {command_search}.")
        print(f"\tPresent statistics / {command_statistics}.")
        print(f"\tExit the program / {command_exit}.")

    @staticmethod
    def print_menu_rent(command_rent: str, command_return: str, command_list: str, command_undo: str, command_redo: str, command_back: str):
        print("Select the desired action:")
        print(f"\tRent a book / {command_rent}.")
        print(f"\tReturn a book / {command_return}.")
        print(f"\tShow rentals / {command_list}.")
        print(f"\tUndo / {command_undo}.")
        print(f"\tRedo / {command_redo}.")
        print(f"\tGo back / {command_back}.")

    @staticmethod
    def print_search_commands(command_book: str, command_client: str, command_back: str):
        print("What do you want to search for?")
        print(f"\tBook / {command_book}.")
        print(f"\tClient / {command_client}.")
        print(f"\tGo back / {command_back}.")

    @staticmethod
    def print_search_books_commands(command_id: str, command_title: str, command_author: str, command_cancel: str):
        print("What do you want to search by?")
        print(f"\tSearch by id / {command_id}.")
        print(f"\tSearch by title / {command_title}.")
        print(f"\tSearch by author / {command_author}.")
        print(f"\tCancel / {command_cancel}.")

    @staticmethod
    def print_search_client_commands(command_id: str, command_name: str, command_cancel: str):
        print("What do you want to search by?")
        print(f"\tSearch by id / {command_id}.")
        print(f"\tSearch by name / {command_name}.")
        print(f"\tCancel / {command_cancel}.")

    @staticmethod
    def print_menu_statistics(command_book: str, command_client: str, command_author: str, command_back: str):
        print("What do you want to view?")
        print(f"\tMost rented books / {command_book}.")
        print(f"\tMost active clients / {command_client}.")
        print(f"\tMost rented authors / {command_author}.")
        print(f"\tGo back / {command_back}.")

    @staticmethod
    def print_undo_menu(command_book: str, command_client: str, command_back):
        print("What do you want to undo?")
        print(f"\tBooks / {command_book}.")
        print(f"\tClients / {command_client}.")
        print(f"\tGo back / {command_back}.")

    @staticmethod
    def print_redo_menu(command_book: str, command_client: str, command_back):
        print("What do you want to redo?")
        print(f"\tBooks / {command_book}.")
        print(f"\tClients / {command_client}.")
        print(f"\tGo back / {command_back}.")


if __name__ == "__main__":
    pass
