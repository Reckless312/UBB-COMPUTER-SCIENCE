import unittest
from src.DomainServices.BookServices import BookServices
from src.DomainServices.ClientServices import ClientServices
from src.Errors.ServicesError import ServicesError


class TestMemory(unittest.TestCase):
    def setUp(self):
        self.book = BookServices()
        self.client = ClientServices()

    def test_books(self):
        self.assertEqual(len(self.book.repository.data), 20)
        self.book.add(21, "book1", "author1")
        self.assertEqual(len(self.book.repository.data), 21)
        self.book.remove(21)
        self.assertEqual(len(self.book.repository.data), 20)
        self.book.update(20, "newtitle1", "newauthor1")
        book = self.book.find_by_id(20)
        self.assertEqual(book.title, "newtitle1")
        self.assertEqual(book.author, "newauthor1")
        try:
            self.book.add(15, "book2", "author2")
        except ServicesError:
            self.assertEqual(len(self.book.repository.data), 20)
        try:
            self.book.remove(25)
        except ServicesError:
            self.assertEqual(len(self.book.repository.data), 20)
        try:
            self.book.update(25, "newtitle2", "newauthor2")
        except ServicesError as se:
            print(se)

    def test_clients(self):
        self.assertEqual(len(self.client.repository.data), 20)
        self.client.add(21, "client1")
        self.assertEqual(len(self.client.repository.data), 21)
        self.client.remove(21)
        self.assertEqual(len(self.client.repository.data), 20)
        self.client.update(20, "newclient1")
        client = self.client.find_by_id(20)
        self.assertEqual(client.name, "newclient1")
        try:
            self.client.add(15, "client2")
        except ServicesError:
            self.assertEqual(len(self.client.repository.data), 20)
        try:
            self.client.remove(25)
        except ServicesError:
            self.assertEqual(len(self.client.repository.data), 20)
        try:
            self.client.update(25, "newclient2")
        except ServicesError as se:
            print(se)
