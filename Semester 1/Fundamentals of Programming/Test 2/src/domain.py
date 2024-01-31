class Address:
    def __init__(self, _id, name, number, x, y):
        self.id = _id
        self.name = name
        self.number = number
        self.x = x
        self.y = y

    def __str__(self):
        return f"ID: {self.id}, Name: {self.name}, Number: {self.number}, X: {self.x}, Y: {self.y}"


if __name__ == "__main__":
    pass
