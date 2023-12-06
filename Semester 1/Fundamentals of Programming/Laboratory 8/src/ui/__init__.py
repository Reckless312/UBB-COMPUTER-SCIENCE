"""
The UI class is presented here, also the program start
"""
from src.services import Services


class UI:
    def __init__(self, memory):
        self.memory = memory

    def start(self):
        repository = self.memory
        print("Starting menu...")
        command_add, command_display, command_filter, command_undo, command_change_memory, command_exit = "1", "2", "3", "4", "5", "0"
        command_memory_repository, command_text_file_repository, command_binary_file_repository = "1", "2", "3"
        while True:
            UI.print_menu(command_add, command_display, command_filter, command_undo, command_change_memory, command_exit)
            user_input = input(">")
            if user_input == command_add:
                try:
                    real_part, imaginary_part = input("a = "), input("b = ")
                    UI.add_complex_number(repository)
                    UI.save_file(repository)
                except ValueError as ve:
                    print(ve)
            elif user_input == command_display:
                repository.display()
            elif user_input == command_filter:
                try:
                    UI.filter_by_positions(repository)
                    UI.save_file(repository)
                except ValueError as ve:
                    print(ve)
            elif user_input == command_undo:
                try:
                    repository.undo()
                    UI.save_file(repository)
                except ValueError as ve:
                    print(ve)
            elif user_input == command_change_memory:
                UI.print_memories(command_memory_repository, command_text_file_repository, command_binary_file_repository)
                new_memory = input("\t>")
                if new_memory == command_memory_repository:
                    if isinstance(repository, MemoryRepository):
                        print("ALREADY USING THE MEMORY-REPOSITORY!")
                    else:
                        repository = MemoryRepository()
                        repository.generate()
                        print("MEMORY CHANGED SUCCESSFULLY")
                elif new_memory == command_text_file_repository:
                    if isinstance(repository, TextFileRepository):
                        print("ALREADY USING THE TEXT-FILE-REPOSITORY!")
                    else:
                        repository = TextFileRepository()
                        repository.load_file()
                        print("MEMORY CHANGED SUCCESSFULLY")
                elif new_memory == command_binary_file_repository:
                    if isinstance(repository, BinaryFileRepository):
                        print("ALREADY USING THE BINARY-FILE-REPOSITORY!")
                    else:
                        repository = BinaryFileRepository()
                        repository.load_file()
                        print("MEMORY CHANGED SUCCESSFULLY")
            elif user_input == command_exit:
                break
            else:
                print("WRONG COMMAND!")

    @staticmethod
    def save_file(repository):
        if isinstance(repository, TextFileRepository) or isinstance(repository, BinaryFileRepository):
            repository.save_file()

    @staticmethod
    def add_complex_number(repository):
        real_part, imaginary_part = input("a = "), input("b = ")
        number = ComplexNumber(real_part, imaginary_part)
        repository.add(number)

    @staticmethod
    def filter_by_positions(repository):
        start, end = input("Starting position: "), input("Ending position: ")
        Services.is_number(start), Services.is_number(end), Services.is_in_numbers(int(start), int(end), repository)
        start, end = int(start), int(end)
        repository.filter(start, end)

    @staticmethod
    def print_menu(command_add: str, command_display: str, command_filter: str, command_undo: str, command_change_memory: str, command_exit: str):
        print(f"\tAdd a number / {command_add}")
        print(f"\tDisplay the list / {command_display}")
        print(f"\tFilter the list / {command_filter}")
        print(f"\tUndo the last operation / {command_undo}")
        print(f"\tChange the reposit / {command_change_memory}")
        print(f"\tExit / {command_exit}")

    @staticmethod
    def print_memories(command_memory_repository: str, command_text_file_repository: str, command_binary_file_repository: str):
        print("\tSelect memory: ")
        print(f"\tMemoryRepository / {command_memory_repository}")
        print(f"\tTextFileRepository / {command_text_file_repository}")
        print(f"\tBinaryFileRepository / {command_binary_file_repository}")


if __name__ == "__main__":
    pass
