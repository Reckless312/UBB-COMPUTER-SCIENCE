import unittest
from src.services.book_services import BookServices
from src.services.client_services import ClientServices
from src.repository.memory_repository import RepositoryError

# First functionality: Manage clients and books. The user can add, remove, update, and list both clients and books.


class TestMemory(unittest.TestCase):
    def setUp(self):
        self.book = BookServices()
        self.client = ClientServices()

    def test_books(self):
        self.assertEqual(len(self.book.repository), 20)
        self.book.add(21, "book1", "author1")
        self.assertEqual(len(self.book.repository), 21)
        self.book.remove(21)
        self.assertEqual(len(self.book.repository), 20)
        self.book.update(20, "newtitle1", "newauthor1")
        book = self.book.repository.find_by_id(20)
        self.assertEqual(book.title, "newtitle1")
        self.assertEqual(book.author, "newauthor1")
        try:
            self.book.add(15, "book2", "author2")
        except RepositoryError:
            self.assertEqual(len(self.book.repository), 20)
        try:
            self.book.remove(25)
        except RepositoryError:
            self.assertEqual(len(self.book.repository), 20)
        try:
            self.book.update(25, "newtitle2", "newauthor2")
        except RepositoryError as re:
            print(re)

    def test_clients(self):
        self.assertEqual(len(self.client.repository), 20)
        self.client.add(21, "client1")
        self.assertEqual(len(self.client.repository), 21)
        self.client.remove(21)
        self.assertEqual(len(self.client.repository), 20)
        self.client.update(20, "newclient1")
        client = self.client.repository.find_by_id(20)
        self.assertEqual(client.name, "newclient1")
        try:
            self.client.add(15, "client2")
        except RepositoryError:
            self.assertEqual(len(self.client.repository), 20)
        try:
            self.client.remove(25)
        except RepositoryError:
            self.assertEqual(len(self.client.repository), 20)
        try:
            self.client.update(25, "newclient2")
        except RepositoryError as re:
            print(re)

