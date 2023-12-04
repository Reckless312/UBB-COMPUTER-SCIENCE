#
# Functions section
#
def sort_flights_to_one_city(compendium_of_flights: list, departure_city: str):
    """
    Sorts flights from one city
    :param compendium_of_flights: all the flights
    :param departure_city: where it's leaving from
    :return: None / -> print
    """
    flights_of_the_desired_city = []
    for one_flight in compendium_of_flights:
        if one_flight["departure city"] == departure_city:
            flights_of_the_desired_city.append(one_flight)
    sorted_flights_of_desired_city = sorted(flights_of_the_desired_city, key=lambda x: x["duration"])
    print_all_flights(sorted_flights_of_desired_city)


def reroute_a_flight(compendium_of_flights: list, initial_destination: str, new_destination: str):
    """
    Reroute a flight because of bad weather
    :param compendium_of_flights: all flights
    :param initial_destination: where we should have reached
    :param new_destination: where we will be going
    :return: Changes the list of dictionaries
    """
    if len(initial_destination) < 3 or len(new_destination) < 3:
        raise ValueError("Doesn't meet the criteria")
    for one_flight in compendium_of_flights:
        if one_flight["destination city"] == initial_destination:
            one_flight["destination city"] = new_destination


def modify_duration_of_a_flight(compendium_of_flights: list, code: str, new_duration: int):
    """
    Introduce a code of a flight and the new duration of it
    :param code: The code of a chosen flight
    :param new_duration: The desired duration
    :param compendium_of_flights: contains all the flights
    :return: the list itself
    """
    is_a_flight = False
    for one_flight in compendium_of_flights:
        if one_flight["code"] == code:
            is_a_flight = True
            one_flight["duration"] = int(new_duration)
    if is_a_flight is False:
        raise ValueError("Doesn't exist")
    if int(new_duration) < 20:
        raise ValueError("Flight < 20 minutes")


def add_a_new_flight(compendium_of_flights: list, code: str, duration: int, departure_city: str, destination_city: str):
    """
    Add a new flight to the compendium
    :param compendium_of_flights: all flights
    :param code: The code of the flight
    :param duration: how much it will take
    :param departure_city: Where we are leaving from
    :param destination_city: Where we will og
    :return: Changes the compendium
    """
    if len(departure_city) < 3 or len(code) < 3 or len(destination_city) < 3 or duration < 20:
        raise ValueError("Flight doesn't fit the conditions")
    compendium_of_flights.append({"code": code, "duration": int(duration), "departure city": departure_city, "destination city": destination_city})

#
# User interface section
#


def read_departure_city():
    """
    Reads departure city
    :return: departure city / str
    """
    departure_city = input("Insert departure city: ")
    return departure_city


def read_to_reroute():
    initial_destination = input("Insert initial destination: ")
    new_destination = input("Insert new destination: ")
    return initial_destination, new_destination


def read_to_modify_flight():
    code = input("Please a existing plane code: ")
    new_duration = int(input("The new duration: "))
    return code, new_duration


def read_a_flights():
    code = input("Insert code: ")
    duration = int(input("Insert duration: "))
    departure_city = input("Insert departure city: ")
    destination_city = input("Insert destination city: ")
    return code, duration, departure_city, destination_city


def print_all_flights(compendium_of_flights: list):
    for one_flight in compendium_of_flights:
        print(one_flight)


def menu():
    compendium_of_flights = []
    print("Starting menu...")
    command_add = "1"
    command_modify = "2"
    command_reroute = "3"
    command_sort = "4"
    while True:
        print(f"\tAdd a new flight / {command_add}")
        print(f"\tModify a flight / {command_modify}")
        print(f"\tReroute a flight / {command_reroute}")
        print(f"\tSort a flight / {command_sort}")
        user_input = input(">")
        if user_input == command_add:
            try:
                code, duration, departure_city, destination_city = read_a_flights()
                add_a_new_flight(compendium_of_flights, code, duration, departure_city, destination_city)
            except ValueError as ve:
                print(ve)
        elif user_input == command_modify:
            try:
                code, new_duration = read_to_modify_flight()
                modify_duration_of_a_flight(compendium_of_flights, code, new_duration)
            except ValueError as ve:
                print(ve)
        elif user_input == command_reroute:
            try:
                initial_destination, new_destination = read_to_reroute()
                reroute_a_flight(compendium_of_flights, initial_destination, new_destination)
            except ValueError as ve:
                print(ve)
        elif user_input == command_sort:
            departure_city = read_departure_city()
            sort_flights_to_one_city(compendium_of_flights, departure_city)
        else:
            print("Invalid Command")


if __name__ == "__main__":
    menu()
