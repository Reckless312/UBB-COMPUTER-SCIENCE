from Repository import Repository
from Services import Services
from ui import UI

if __name__ == "__main__":
    repo = Repository()
    service = Services(repo)
    ui = UI(service)
    ui.start()
