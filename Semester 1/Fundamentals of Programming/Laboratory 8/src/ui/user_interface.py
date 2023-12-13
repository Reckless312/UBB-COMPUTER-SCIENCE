from src.repository.memory_repository import RepositoryError
from src.services.book_services import BookServices
from src.services.client_services import ClientServices
from src.services.rental_services import RentalServices


class UI:
    def __init__(self):
        self.book = BookServices()
        self.client = ClientServices()
        self.rental = RentalServices(self.book.repository, self.client.repository)

    def start(self):
        print("Starting program...")
        command_manage, command_rent, command_search, command_statistics, command_exit = "1", "2", "3", "4", "0"
        while True:
            self.print_main_menu(command_manage, command_rent, command_search, command_statistics, command_exit)
            menu_command = input(">")
            if menu_command == command_manage:
                self.start_manage()
            elif menu_command == command_rent:
                self.start_rent()
            elif menu_command == command_search:
                self.start_search()
            elif menu_command == command_statistics:
                self.start_statistics()
            elif menu_command == command_exit:
                break
            else:
                print("Invalid command.")

    def start_manage(self):
        command_add, command_remove, command_update, command_list, command_exit = "1", "2", "3", "4", "0"
        command_book, command_client, command_back = "1", "2", "0"
        while True:
            self.print_manage_menu(command_add, command_remove, command_update, command_list, command_exit)
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
                elif managing_object_command == command_client:
                    try:
                        _id, client_name = input("Insert id: "), input("Insert client: ")
                        self.client.add(_id, client_name)
                    except RepositoryError as re:
                        print(re)
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
                elif remove_command == command_client:
                    try:
                        remove_id = input("Id to be deleted: ")
                        self.client.remove(remove_id)
                    except RepositoryError as re:
                        print(re)
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
                elif update_command == command_client:
                    try:
                        _id, client_name = input("Insert id: "), input("Insert new client name: ")
                        self.client.update(_id, client_name)
                    except RepositoryError as re:
                        print(re)
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
            elif menu_managing_command == command_exit:
                break
            else:
                print("Invalid command.")

    def start_rent(self):
        command_rent, command_return, command_list, command_back = "1", "2", "3", "0"
        while True:
            self.print_menu_rent(command_rent, command_return, command_list, command_back)
            rental_command = input(">")
            if rental_command == command_rent:
                try:
                    book_id, client_id = input("Select the id of a book: "), input("Select your id: ")
                    self.rental.rent_book(book_id, client_id)
                except RepositoryError as re:
                    print(re)
            elif rental_command == command_return:
                try:
                    rental_id = input("Select the rental id: ")
                    self.rental.return_book(rental_id)
                except RepositoryError as re:
                    print(re)
            elif rental_command == command_list:
                rentals = self.rental.list_to_screen()
                for rental in rentals:
                    print(rental)
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
                        book = self.book.search_with_id(_id)
                        print(book)
                    except RepositoryError as re:
                        print(re)
                elif search_attribute == command_title:
                    try:
                        title = input("Insert title: ")
                        books = self.book.search_with_title(title)
                        for book in books:
                            print(book)
                    except RepositoryError as re:
                        print(re)
                elif search_attribute == command_author:
                    try:
                        author = input("Insert author: ")
                        books = self.book.search_with_author(author)
                        for book in books:
                            print(book)
                    except RepositoryError as re:
                        print(re)
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
                        client = self.client.search_with_id(_id)
                        print(client)
                    except RepositoryError as re:
                        print(re)
                elif search_attribute == command_name:
                    try:
                        client_name = input("Insert name: ")
                        clients = self.client.search_with_name(client_name)
                        for client in clients:
                            print(client)
                    except RepositoryError as re:
                        print(re)
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
            elif statistics_command == command_client:
                try:
                    clients = self.rental.clients_with_most_rentals()
                    for client in clients:
                        print(client)
                except RepositoryError as re:
                    print(re)
            elif statistics_command == command_author:
                authors = self.rental.most_rented_author()
                for author in authors:
                    print(author)
            elif statistics_command == command_back:
                break
            else:
                print("Invalid command.")

    @staticmethod
    def print_manage_menu(command_add: str, command_remove: str, command_update: str, command_list: str, command_back: str):
        print("Select the managing method:")
        print(f"\tAdd a new object / {command_add}.")
        print(f"\tRemove one object / {command_remove}.")
        print(f"\tUpdate an object / {command_update}.")
        print(f"\tShow on screen an object / {command_list}.")
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
    def print_menu_rent(command_rent: str, command_return: str, command_list: str, command_back: str):
        print("Select the desired action:")
        print(f"\tRent a book / {command_rent}.")
        print(f"\tReturn a book / {command_return}.")
        print(f"\tShow rentals / {command_list}.")
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


if __name__ == "__main__":
    pass
