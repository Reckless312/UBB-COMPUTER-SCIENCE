from src.BinaryFileRepositories.BinaryFileBookRepository import BinaryFileBookRepository
from src.BinaryFileRepositories.BinaryFileClientRepository import BinaryFileClientRepository
from src.BinaryFileRepositories.BinaryFileRentalRepository import BinaryFileRentalRepository
from src.DomainRepositories.BookRepository import BookRepository
from src.DomainRepositories.ClientRepository import ClientRepository
from src.DomainRepositories.RentalRepository import RentalRepository
from src.TextFileRepositories.TextFileBookRepository import TextFileBookRepository
from src.TextFileRepositories.TextFileClientRepository import TextFileClientRepository
from src.TextFileRepositories.TextFileRentalRepository import TextFileRentalRepository
from src.UI.UI import UI
import configparser
if __name__ == "__main__":
    user_interface = UI()
    config = configparser.RawConfigParser()
    config.read('settings.properties')
    repository_config = config.get('Repositories', 'repository')
    if repository_config == "inmemory":
        user_interface.book.repository = BookRepository()
        user_interface.book.generate_books()
        user_interface.client.repository = ClientRepository()
        user_interface.client.generate_clients()
        user_interface.rental.repository = RentalRepository()
        user_interface.rental.books_repository = user_interface.book.repository
        user_interface.rental.clients_repository = user_interface.client.repository
        user_interface.rental.generate_rentals()
    elif repository_config == "binaryfiles":
        user_interface.book.repository = BinaryFileBookRepository(config.get('Repositories', 'books'))
        user_interface.book.repository.load_binary_file()
        user_interface.client.repository = BinaryFileClientRepository(config.get('Repositories', 'clients'))
        user_interface.client.repository.load_binary_file()
        user_interface.rental.repository = BinaryFileRentalRepository(config.get('Repositories', 'rentals'))
        user_interface.rental.books_repository = user_interface.book.repository
        user_interface.rental.clients_repository = user_interface.client.repository
        user_interface.rental.repository.load_binary_file()
    elif repository_config == "textfiles":
        user_interface.book.repository = TextFileBookRepository(config.get('Repositories', 'books'))
        user_interface.book.repository.load_text_file()
        user_interface.client.repository = TextFileClientRepository(config.get('Repositories', 'clients'))
        user_interface.client.repository.load_text_file()
        user_interface.rental.repository = TextFileRentalRepository(config.get('Repositories', 'rentals'))
        user_interface.rental.books_repository = user_interface.book.repository
        user_interface.rental.clients_repository = user_interface.client.repository
        user_interface.rental.repository.load_text_file()
    user_interface.start()
