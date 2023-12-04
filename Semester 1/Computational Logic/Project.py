"""
Make an application with the following functions:
    - arithmetic operations for positive integers : addition
                            subtraction
                            multiplication
                            division (by one digit)
                            // all for a base p = {2, 3, 4, ... , 16}
    - conversion of natural numbers between two bases (from 2 to 16) via substitution / successive divisions
                                                     and rapid conversions
    - menu, so they can be done separately
"""


"""
Functions that convert to a different base
"""


"""
Functions that check proprieties
"""


def is_a_positive_integer(number: str):
    if isinstance(number, int) and int(number) >= 0:
        pass
    else:
        raise ValueError("NOT A CORRECT ARGUMENT")


def is_a_base(number: str):
    if isinstance(number, int) and 2 <= int(number) <= 16:
        pass
    else:
        raise ValueError("NOT A CORRECT ARGUMENT")


"""
User Interface
"""


def print_operations(command_add: str, command_sub: str, command_mul: str, command_div: str, command_back: str):
    print(f"\tAddition / {command_add}")
    print(f"\tSubtraction / {command_sub}")
    print(f"\tMultiplication / {command_mul}")
    print(f"\tDivision / {command_div}")
    print(f"\tGo back / {command_back}")


def print_conversions(command_substitution: str, command_divisions: str, command_rapid_conversions: str, command_back: str):
    print(f"\tSubstitution method / {command_substitution}")
    print(f"\tSuccessive divisions / {command_divisions}")
    print(f"\tRapid conversions / {command_rapid_conversions}")
    print(f"\tGo back / {command_back}")


def print_options(command_operations: str, command_conversions: str, command_exit: str):
    print(f"\tArithmetic operations / {command_operations}")
    print(f"\tConversions / {command_conversions}")
    print(f"\tExit / {command_exit}")


def menu():
    command_operations, command_conversions, command_exit = "1", "2", "0"
    print("Starting menu...")
    while True:
        print_options(command_operations, command_conversions, command_exit)
        user_input_options = input(">")
        if user_input_options == command_operations:
            print("Choose the desired operation: ")
            command_add, command_sub, command_mul, command_div, command_back = "1", "2", "3", "4", "0"
            print_operations(command_add, command_sub, command_mul, command_div, command_back)
            user_input_operation = input(">")
            if user_input_operation == command_add:
                print("\tRead two numbers")
                number_one = input("First number: ")
                number_two = input("Second number: ")
                print("\tRead the desired base")
                base = input("Base = ")
                try:
                    is_a_positive_integer(number_one)
                    is_a_positive_integer(number_two)
                    is_a_base(base)
                except ValueError as ve:
                    print(ve)
            elif user_input_operation == command_sub:
                pass
            elif user_input_operation == command_mul:
                pass
            elif user_input_operation == command_div:
                pass
            elif user_input_operation == command_back:
                pass
            else:
                print("INSERT A VALID OPERATION")
        elif user_input_options == command_conversions:
            command_substitution, command_divisions, command_rapid_conversions, command_back = "1", "2", "3", "0"
            print_conversions(command_substitution, command_divisions, command_rapid_conversions, command_back)
            user_input_conversion = input(">")
            if user_input_conversion == command_substitution:
                pass
            elif user_input_conversion == command_divisions:
                pass
            elif user_input_conversion == command_rapid_conversions:
                pass
            elif user_input_conversion == command_back:
                pass
            else:
                print("INSERT A VALID CONVERSION")
        elif user_input_options == command_exit:
            break
        else:
            print("INSERT A VALID COMMAND")


if __name__ == "__main__":
    menu()
