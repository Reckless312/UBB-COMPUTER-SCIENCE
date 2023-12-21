from src.DomainRepositories.BookRepository import BookRepository


class TextFileBookRepository(BookRepository):
    def __init__(self, file_name: str = "data.bin"):
        super().__init__()
        self.file = file_name

    def load_text_file(self):
        try:
            file = open(self.file, "r")
            for line in file:
                book = line[:-1].split()
                _id, after_keyword, book_title, book_author = 1, 4, "", ""
                while book[after_keyword] != '-':
                    book_title = book_title + book[after_keyword] + " "
                    after_keyword += 1
                after_keyword += 2
                book_title = book_title.split()
                book_title = " ".join(book_title)
                while after_keyword <= len(book) - 1:
                    book_author = book_author + book[after_keyword] + " "
                    after_keyword += 1
                book_author = book_author.split()
                book_author = " ".join(book_author)
                self.add(self.create_book(int(book[_id]), book_title, book_author))
            file.close()
        except FileNotFoundError:
            print("NO FILE TO OPEN!")

    def save_text_file(self):
        file = open(self.file, "w")
        for book in self.data.keys():
            file.write("%s\n" % self.data[book])
        file.close()
