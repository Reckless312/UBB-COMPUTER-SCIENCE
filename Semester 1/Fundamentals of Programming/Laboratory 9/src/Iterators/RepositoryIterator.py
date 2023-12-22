class RepositoryIterator:
    def __init__(self, data: list):
        self._data = data
        self._pos = -1

    def __next__(self):
        self._pos += 1
        if self._pos == len(self._data):
            raise StopIteration()
        return self._data[self._pos]


if __name__ == "__main__":
    pass
