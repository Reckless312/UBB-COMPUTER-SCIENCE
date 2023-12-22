import unittest
from src.DomainServices.BookServices import BookServices
from src.DomainServices.ClientServices import ClientServices
from src.Errors.ServicesError import ServicesError


class TestMemory(unittest.TestCase):
    def setUp(self):
        self.book = BookServices()
        self.client = ClientServices()

    def test_books(self):
        self.assertEqual(len(self.book.repository.data), 0)
        self.book.add(1, "book1", "author1")
        self.assertEqual(len(self.book.repository.data), 1)
        self.book.repository.remove(1)
        self.assertEqual(len(self.book.repository.data), 0)
        self.book.add(1, "book1", "author1")
        self.book.repository.update(self.book.repository.create_book(1, "newtitle1", "newauthor1"))
        book = self.book.find_by_id(1)
        self.assertEqual(book.title, "newtitle1")
        self.assertEqual(book.author, "newauthor1")
        try:
            self.book.add(1, "book2", "author2")
        except ServicesError:
            self.assertEqual(len(self.book.repository.data), 1)
        try:
            self.book.remove(2)
        except ServicesError:
            self.assertEqual(len(self.book.repository.data), 1)
        try:
            self.book.update(2, "newtitle2", "newauthor2")
        except ServicesError as se:
            print(se)

    def test_clients(self):
        self.assertEqual(len(self.client.repository.data), 0)
        self.client.add(1, "client1")
        self.assertEqual(len(self.client.repository.data), 1)
        self.client.repository.remove(1)
        self.assertEqual(len(self.client.repository.data), 0)
        self.client.add(1, "client1")
        self.client.repository.update(self.client.repository.create_client(1, "newclient1"))
        client = self.client.find_by_id(1)
        self.assertEqual(client.name, "newclient1")
        try:
            self.client.add(1, "client2")
        except ServicesError:
            self.assertEqual(len(self.client.repository.data), 1)
        try:
            self.client.remove(2)
        except ServicesError:
            self.assertEqual(len(self.client.repository.data), 1)
        try:
            self.client.update(25, "newclient2")
        except ServicesError as se:
            print(se)
