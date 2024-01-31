import configparser

from src.Game import Game
from src.Services import Service
from src.UI import UI

if __name__ == "__main__":
    config = configparser.RawConfigParser()
    config.read('settings.properties')
    N = config.get('Snake', 'N')
    Apples = config.get('Snake', 'Apples')
    game = Game(int(N), int(Apples))
    service = Service(game)
    ui = UI(service)
    ui.start()
