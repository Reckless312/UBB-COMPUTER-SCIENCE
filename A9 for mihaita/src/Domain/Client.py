from src.Domain.IdObject import ID


class Client(ID):
    def __init__(self, _id, name):
        super().__init__(_id)
        self.__name = name
        self.__days_of_rents = 0

    def __str__(self):
        return f"ID: {self.id} - Name: {self.__name}"

    def __repr__(self):
        return str(self)

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, name):
        self.__name = name


def import_20_clients():
    """
    Creates 20 hard - coded clients
    :return: list
    """
    clients = []
    _id = 1
    name = ["Jaylynn Vasquez", "Yuliana Kelley", "Jayson Kemp", "Cedric Jones", "Margaret Valentine", "Cesar Best", "Darian Zuniga", "Kameron Blankenship", "Ellis Torres", "Joe Miller", "Hamza Garza", "Yaritza Burton", "Mayra Merritt", "Samson Moses", "Howard Mays", "Vaughn Osborne", "Nevaeh Mcmillan", "Lukas Keith", "Jewel Atkins", "Akira Harris"]
    for i in range(20):
        clients.append(Client(_id + i, name[i]))
    return clients


if __name__ == "__main__":
    pass
