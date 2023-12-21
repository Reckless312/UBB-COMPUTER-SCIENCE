from src.Domain.IdObject import ID
from src.Errors.RepositoryError import RepositoryError
from src.Iterators.RepositoryIterator import RepositoryIterator


class MemoryRepository:
    def __init__(self):
        self._data = {}

    def __len__(self):
        return len(self._data)

    def __iter__(self):
        return RepositoryIterator(list(self._data.values()))

    def __getitem__(self, item):
        if item not in self.data:
            return None
        return self.data[item]

    def add(self, domain_object: ID):
        if not isinstance(domain_object, ID):
            raise RepositoryError("The object is not a subclass of ID")
        self._data[domain_object.id] = domain_object

    def remove(self, _id):
        return self._data.pop(_id, None)

    def update(self, domain_object: ID):
        if not isinstance(domain_object, ID):
            raise RepositoryError("The object is not a subclass of ID")
        self._data[domain_object.id] = domain_object

    def list(self):
        objects = []
        for domain_object in self._data:
            objects.append(self._data[domain_object])
        return objects

    @property
    def data(self):
        return self._data

    @data.setter
    def data(self, new_data):
        self._data = new_data


if __name__ == "__main__":
    pass
