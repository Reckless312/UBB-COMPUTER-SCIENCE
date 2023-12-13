class RepositoryIterator:
    """
    Implements iteration for the MemoryRepository class
    """
    def __init__(self, data: list):
        self.data = data
        self.pos = -1

    def __next__(self):
        self.pos += 1
        if self.pos == len(self.data):
            raise StopIteration()
        return self.data[self.pos]


class RepositoryError(Exception):
    """
    Special class to raise its own errors
    """
    def __init__(self, message_error="Repository Error!"):
        self.message = message_error
        super().__init__(self.message)


class MemoryRepository:
    """
    Repository class that we would store a dictionary to work with
    """
    def __init__(self):
        self.data = {}

    def __iter__(self):
        return RepositoryIterator(list(self.data.values()))

    def __len__(self):
        return len(self.data)

    def __getitem__(self, item):
        if item not in self.data:
            return None
        return self.data[item]

    def add(self, domain_object):
        """
        Adds ab object to the repository
        :param domain_object: Book / Client / Rental
        :return: changes repository
        """
        if self.find_by_id(domain_object.id) is not None:
            raise RepositoryError("Object already exists.")
        self.data[domain_object.id] = domain_object

    def remove(self, _id: int):
        """
        Removes an object from the repository via id
        :param _id: representation of object
        :return: changes list / RepositoryError
        """
        if self.find_by_id(_id) is None:
            raise RepositoryError("Object doesn't exist.")
        return self.data.pop(_id, None)

    def find_by_id(self, _id: int):
        """
        Returns the object via id
        :param _id: representation of object
        :return: Client / Book / Rental / None
        """
        return self.data[_id] if _id in self.data.keys() else None

    def update(self, domain_object):
        """
        Updates an existing object
        :param domain_object: Client / Book / Rental
        :return: changes list / RepositoryError
        """
        if domain_object.id not in self.data.keys():
            raise RepositoryError("Object doesn't exists.")
        self.data[domain_object.id] = domain_object

    def list(self):
        """
        Lists all object in repository
        :return: None
        """
        objects = []
        for domain_object in self.data:
            objects.append(self.data[domain_object])
        return objects


if __name__ == "__main__":
    pass
