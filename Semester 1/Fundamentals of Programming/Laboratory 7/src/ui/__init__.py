"""
The UI class is presented here, connects with Services
"""
from src.services import Services


class UI:
    def __init__(self):
        """
        No need to declare anything
        """
        pass
    """
    Declaring it outside the constructor to be allowed to build a variable with UI class, without specifying
    any other variables inside
    """
    instruction = Services()

    def start(self):
        """
        Shows menu / calls functions from inside the Services class
        :return: None
        """
        print("Starting menu...")
        command_add, command_display, command_filter, command_undo, command_exit = "1", "2", "3", "4", "0"
        while True:
            UI.print_menu(command_add, command_display, command_filter, command_undo, command_exit)
            user_input = input(">")
            if user_input == command_add:
                try:
                    real_part, imaginary_part = input("Select real part: "), input("Select imaginary part: ")
                    self.instruction.add(real_part, imaginary_part)
                except ValueError as ve:
                    print(ve)
            elif user_input == command_display:
                self.instruction.display()
            elif user_input == command_filter:
                try:
                    start, end = input("Starting position: "), input("Ending position: ")
                    self.instruction.filter(start, end)
                except ValueError as ve:
                    print(ve)
            elif user_input == command_undo:
                try:
                    self.instruction.undo()
                except ValueError as ve:
                    print(ve)
            elif user_input == command_exit:
                break
            else:
                print("WRONG COMMAND!")

    @staticmethod
    def print_menu(command_add: str, command_display: str, command_filter: str, command_undo: str, command_exit: str):
        """
        Used for code simplicity inside menu
        :param command_add: "1"
        :param command_display: "2"
        :param command_filter: "3"
        :param command_undo: "4"
        :param command_exit: "0"
        :return: None
        """
        print(f"\tAdd a number / {command_add}")
        print(f"\tDisplay the list / {command_display}")
        print(f"\tFilter the list / {command_filter}")
        print(f"\tUndo the last operation / {command_undo}")
        print(f"\tExit / {command_exit}")


if __name__ == "__main__":
    """
    We pass, no need to call anything
    """
    pass
