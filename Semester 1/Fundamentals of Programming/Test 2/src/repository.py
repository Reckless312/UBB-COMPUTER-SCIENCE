from src.domain import Address
import math


class TextFileRepository:
    def __init__(self, addresses_file: str = "addresses_file.txt"):
        self.file = addresses_file
        self.addresses = []
        self.read_file()

    def add(self, _id, name, number, x, y):
        self.addresses.append(Address(_id, name, number, x, y))

    def return_addresses(self):
        return self.addresses

    def available_places_for_a_station(self, x, y, d):
        """
        Returns a list of all locations that meet the requirement that the Euclidean distance is less or equal to variable d
        :param x: position x
        :param y: position y
        :param d: distance
        :return: possible locations for a station
        """
        possible_locations = []
        for one_address in self.addresses:
            euclidean_distance = math.sqrt(math.pow(one_address.x - x, 2) + math.pow(one_address.y - y, 2))
            if euclidean_distance <= d:
                possible_locations.append((one_address, euclidean_distance))
        return possible_locations

    def read_file(self):
        with open(self.file, "r") as file:
            for line in file.readlines():
                self.addresses.append(Address(*self.read_line(line)))

    @staticmethod
    def read_line(line: str):
        _id, name, number, x, y = line.split(",")
        return int(_id.strip()), name.strip(), int(number.strip()), int(x.strip()), int(y.strip())

    def find_best_location_for_a_station(self):
        best_x, best_y = None, None
        most_distance = 1000000000000
        for x in range(-100, 101):
            for y in range(-100, 101):
                total_distance = 0
                is_it_solution = True
                for one_address in self.addresses:
                    if one_address.x == x and one_address.y == y:
                        is_it_solution = False
                    euclidean_distance = math.sqrt(math.pow(one_address.x - x, 2) + math.pow(one_address.y - y, 2))
                    total_distance += euclidean_distance
                if total_distance < most_distance and is_it_solution:
                    most_distance = total_distance
                    best_x = x
                    best_y = y
        return best_x, best_y


if __name__ == "__main__":
    pass
