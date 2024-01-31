from src.repository import TextFileRepository


class Services:
    def __init__(self, repository: TextFileRepository):
        self.repository = repository

    def add(self, _id, name, number, x, y):
        try:
            _id = int(_id)
            number = int(number)
            x = int(x)
            y = int(y)
        except ValueError:
            raise TypeError("Not integers")
        if _id < 0:
            raise TypeError("Not a positive id number")
        addresses_implemented = self.repository.return_addresses()
        for one_address in addresses_implemented:
            if one_address.id == _id:
                raise TypeError("Id already implemented")
        if len(name) < 3:
            raise TypeError("Not enough letters")
        if not(0 <= number <= 100):
            raise TypeError("Number out of bounds")
        if not(-100 <= x <= 100):
            raise TypeError("X out of bounds")
        if not (-100 <= y <= 100):
            raise TypeError("Y out of bounds")
        self.repository.add(_id, name, number, x, y)

    def get_addresses(self):
        return self.repository.return_addresses()

    def get_places_for_a_station(self, x, y, d):
        """
        Checks for errors and returns the result of the repository call
        :param x: position x
        :param y: position y
        :param d: distance
        :return: list
        """
        try:
            x = int(x)
            y = int(y)
            d = int(d)
        except ValueError:
            raise TypeError("Not integers")
        if not(-100 <= x <= 100):
            raise TypeError("X out of bounds")
        if not (-100 <= y <= 100):
            raise TypeError("Y out of bounds")
        return self.repository.available_places_for_a_station(x, y, d)

    def get_new_taxi_station_location_to_minimize_total_distance(self):
        return self.repository.find_best_location_for_a_station()


if __name__ == "__main__":
    pass
