from src.domain.rental import Rental, import_20_rentals
from src.repository.memory_repository import MemoryRepository
from src.repository.memory_repository import RepositoryError


class RentalRepository(MemoryRepository):
    def __init__(self):
        super().__init__()

    def generate_20_rentals(self):
        """
        Generates 20 rentals
        :return: list with rentals
        """
        rentals = import_20_rentals()
        for rental in rentals:
            self.add(rental)
            rental.book.number_of_rents += 1

    def check_book(self, book_id):
        """
        Checks if a book was rented
        :param book_id: representation to find book
        :return: RepositoryError / None
        """
        for a_book in self.data.values():
            if a_book.book.id == book_id:
                raise RepositoryError("Already rented.")

    @staticmethod
    def create_rental(rental_id, book_id, client_id, rent_date, return_date):
        """
        Creates rental
        :param rental_id: representation of rental object
        :param book_id: representation of book object
        :param client_id: representation of client object
        :param rent_date: the start date of rent
        :param return_date: the last date of rent
        :return: Rental
        """
        return Rental(rental_id, book_id, client_id, rent_date, return_date)
