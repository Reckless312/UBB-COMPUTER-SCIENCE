from src.domain.idObject import ID


class Book(ID):
    """
    Type book represented by an id, a title and an author
    """
    def __init__(self, _id, title, author):
        super().__init__(_id)
        self.title = title
        self.author = author
        self.number_of_rents = 1

    def __str__(self):
        return f"{self.id} - {self.title}, by {self.author}"

    def __repr__(self):
        return str(self)

    @property
    def get_rent_number(self):
        """
        Returns the number that one of the books got rented for
        :return: int
        """
        return self.number_of_rents


def import_20_books():
    """
    Creates 20 hard - coded books
    :return: list
    """
    books = []
    _id = 1
    title = ["Gone with the Wind", "Jane Eyre", "Pride and Prejudice", "To Kill a Mockingbird", "The Hobbit", "Wuthering Heights", "Little Women", "A Tale of Two Cities", "Alice's Adventures in Wonderland", "Anne of Green Gables", "The Wonderful Wizard of Oz", "Emma", "The Raven", "Les Miserables", "Doctor Zhivago", "Treasure Island", "The Complete Grimm's Fairy Tales", "A Little Princess", "A Murder Is Announced", "The Mysterious Affair at Styles"]
    author = ["Margaret Mitchell", "Charlotte Bronte", "Jane Austen", "Harper Lee", "J.R.R Tolkien", "Emily Bronte", "Louisa May Alcott", "Charles Dickens", "Lewis Carroll", "L.M.Montgomery", "L.Frank Baum", "Jane Austen", "Edgar Allan Poe", "Victor Hugo", "Boris Pasternak", "Robert Louis Stevenson", "Jacob Grimm", "Frances Hodgson Burnett", "Agatha Christie", "Agatha Christie"]
    for i in range(20):
        books.append(Book(_id + i, title[i], author[i]))
    return books


if __name__ == "__main__":
    pass
