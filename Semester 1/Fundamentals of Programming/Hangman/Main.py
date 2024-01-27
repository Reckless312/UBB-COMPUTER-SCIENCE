from Game import Game
from Repository import Repository
from Services import Services
from UI import UI

#Doesn't contain all of the specifications and unit tests.
if __name__ == "__main__":
    repo = Repository()
    service = Services(repo)
    game = Game(repo)
    ui = UI(service, game)
    ui.start()
