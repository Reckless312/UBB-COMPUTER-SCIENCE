from datetime import datetime

from src.DomainRepositories.RentalRepository import RentalRepository
from src.Errors.RepositoryError import RepositoryError


class TextFileRentalRepository(RentalRepository):
    def __init__(self, file_name: str = "data.bin"):
        super().__init__()
        self.file = file_name

    def load_text_file(self):
        try:
            counter = 1
            _id_rental, _id_book, title, author, _id_client, name, start_date, end_date = "", "", "", "", "", "", "", ""
            modulo_5, is_one, is_two, is_three, is_four, is_zero = 5, 1, 2, 3, 4, 0
            date_format = "%Y-%m-%d %H:%M:%S"
            file = open(self.file, "r")
            for line in file:
                if counter % modulo_5 == is_one:
                    _id = line[:-1].split()
                    position_id = 1
                    _id_rental = int(_id[position_id])
                elif counter % modulo_5 == is_two:
                    book = line[:-1].split()
                    _id, after_keyword, title, author = 2, 5, "", ""
                    while book[after_keyword] != '-':
                        title = title + book[after_keyword] + " "
                        after_keyword += 1
                    after_keyword += 2
                    title = title.split()
                    title = " ".join(title)
                    while after_keyword <= len(book) - 1:
                        author = author + book[after_keyword] + " "
                        after_keyword += 1
                    author = author.split()
                    author = " ".join(author)
                    _id_book = book[_id]
                elif counter % modulo_5 == is_three:
                    client = line[:-1].split()
                    _id, after_keyword, name = 2, 5, ""
                    while after_keyword <= len(client) - 1:
                        name = name + client[after_keyword] + " "
                        after_keyword += 1
                    name = name.split()
                    name = " ".join(name)
                    _id_client = client[_id]
                elif counter % modulo_5 == is_four:
                    date = line[:-1].split()
                    position_year_month_day, position_hours = 2, 3
                    start_date = date[position_year_month_day] + " " + date[position_hours]
                    start_date = datetime.strptime(start_date, date_format)
                elif counter % modulo_5 == is_zero:
                    date = line[:-1].split()
                    position_year_month_day, position_hours = 2, 3
                    end_date = date[position_year_month_day] + " " + date[position_hours]
                    end_date = datetime.strptime(end_date, date_format)
                    self.add(self.create_rental(_id_rental, self.create_book(int(_id_book), title, author), self.create_client(int(_id_client), name), start_date, end_date))
                counter += 1
        except FileNotFoundError:
            print("NO FILE TO OPEN!")

    def save_text_file(self):
        file = open(self.file, "w")
        for client in self.data.keys():
            file.write("%s\n" % self.data[client])
        file.close()
