"""
Assignment 4
This package has been created to call the UI
The program tries to follow the following structure
Main -> UI -> Services -> MemoryRepository -> Domains (with some exceptions)
"""
from src.ui.user_interface import UI

if __name__ == "__main__":
    user_interface = UI()
    user_interface.start()

