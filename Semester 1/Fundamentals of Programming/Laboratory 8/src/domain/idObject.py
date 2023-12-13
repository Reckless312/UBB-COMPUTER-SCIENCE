class ID:
    def __init__(self, _id: int):
        if not isinstance(_id, int):
            raise TypeError("Id cannot be non - integer.")
        self.id = _id


if __name__ == "__main__":
    pass
