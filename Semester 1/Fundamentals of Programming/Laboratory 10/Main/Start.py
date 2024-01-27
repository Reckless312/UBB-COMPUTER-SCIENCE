"""
Assignment 1 - Connect Four -
"""
from UserInterfaces.UI import UI
from UserInterfaces.GUI import GUI
import configparser


if __name__ == "__main__":
    config = configparser.RawConfigParser()
    config.read('settings.properties')
    user_interface_config = config.get('UserInterface', 'Interface')
    if user_interface_config == "UI":
        ui = UI()
        ui.start()
    else:
        gui = GUI()
        gui.start_pygame()
