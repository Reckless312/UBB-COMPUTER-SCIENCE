from src.repository import TextFileRepository
from src.services import Services


class UI:
    def __init__(self, services: Services):
        self.services = services
        self.first_option = "1"
        self.second_option = "2"
        self.third_option = "3"
        self.fourth_option = "4"
        self.exit_option = "0"

    def start(self):
        while True:
            print("Select desired command")
            print(f"Add an address / {self.first_option}")
            print(f"Display addresses / {self.second_option}")
            print(f"Check places / {self.third_option}")
            print(f"Find a new possible station / {self.fourth_option}")
            print(f"Exit / {self.exit_option}")
            input_command = input(">")
            if input_command == self.first_option:
                try:
                    _id, name, number, x, y = input("ID: "), input("Name: "), input("Number: "), input("X: "), input("Y: ")
                    self.services.add(_id, name, number, x, y)
                except TypeError as te:
                    print(te)
            elif input_command == self.second_option:
                addresses = self.services.get_addresses()
                for address in addresses:
                    print(address)
            elif input_command == self.third_option:
                try:
                    x, y, d = input("X: "), input("Y: "), input("D: ")
                    available_locations = self.services.get_places_for_a_station(x, y, d)
                    for one_location in available_locations:
                        print(one_location[0])
                        print(f"Total distance: {one_location[1]}")
                except TypeError as te:
                    print(te)
            elif input_command == self.fourth_option:
                x, y = self.services.get_new_taxi_station_location_to_minimize_total_distance()
                print(f"X: {x}, Y: {y}")
            elif input_command == self.exit_option:
                break
            else:
                print("Invalid input.")


if __name__ == "__main__":
    repository = TextFileRepository()
    services = Services(repository)
    ui = UI(services)
    ui.start()
