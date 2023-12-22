from src.BinaryFileRepositories.BinaryFileClientRepository import BinaryFileClientRepository
from src.Domain.Client import import_20_clients
from src.DomainRepositories.ClientRepository import ClientRepository
from src.DomainServices.Command import Command
from src.DomainServices.UndoRedo import UndoRedoService, Operation
from src.Errors.ServicesError import ServicesError
from src.TextFileRepositories.TextFileClientRepository import TextFileClientRepository


class ClientServices:
    def __init__(self):
        self.repository = ClientRepository()
        self.undo_service = UndoRedoService()

    rental_services = None

    def add(self, _id, client_name):
        try:
            _id = int(_id)
        except ValueError:
            raise ServicesError("Not an integer.")
        if self.find_by_id(_id) is not None:
            raise ServicesError("Object already exists.")
        self.repository.add(self.repository.create_client(_id, client_name))
        if isinstance(self.repository, TextFileClientRepository):
            self.repository.save_text_file()
        if isinstance(self.repository, BinaryFileClientRepository):
            self.repository.save_binary_file()
        redo = Command(self.repository.add, (self.repository.create_client(_id, client_name)))
        undo = Command(self.remove, _id)
        self.undo_service.register(Operation(undo, redo))

    def do_commands(self, commands):
        for command in commands:
            command()

    def remove(self, _id):
        try:
            _id = int(_id)
        except ValueError:
            raise ServicesError("Not an integer.")
        if self.find_by_id(_id) is None:
            raise ServicesError("Object doesn't exist.")
        old_rental = self.rental_services.get_rental_id_from_client(_id)
        if old_rental is not None:
            undo_commands = [Command(self.repository.add, self.repository.create_client(_id, self.find_by_id(_id).name)), Command(self.rental_services.did_client_rent, _id)]
            for rental in old_rental:
                undo_commands.append(Command(self.rental_services.repository.add, self.rental_services.repository.create_rental(self.rental_services.rent - 1, rental.book, rental.client, rental.start_date, rental.end_date)))
                self.rental_services.rent += 1
            undo = Command(self.do_commands, undo_commands)
            redo_commands = [Command(self.repository.remove, _id), Command(self.rental_services.did_client_rent, _id)]
            redo = Command(self.do_commands, redo_commands)
            self.repository.remove(_id)
            self.rental_services.did_client_rent(_id)
            self.undo_service.register(Operation(undo, redo))
        else:
            undo = Command(self.repository.add, self.repository.create_client(_id, self.find_by_id(_id).name))
            redo = Command(self.repository.remove, _id)
            self.repository.remove(_id)
            self.undo_service.register(Operation(undo, redo))
        if isinstance(self.repository, TextFileClientRepository):
            self.repository.save_text_file()
        if isinstance(self.repository, BinaryFileClientRepository):
            self.repository.save_binary_file()

    def update(self, _id, name):
        try:
            _id = int(_id)
        except ValueError:
            raise ServicesError("Not an integer.")
        if _id not in self.repository.data.keys():
            raise ServicesError("Object doesn't exist.")
        old_rental = self.rental_services.get_rental_id_from_client(_id)
        old_client = self.find_by_id(_id)
        old_name = str(old_client.name)
        if old_rental is not None:
            undo_commands = [Command(self.repository.update, (self.repository.change_client(old_client, old_name)))]
            for rental in old_rental:
                old_name = str(old_client.name)
                undo_commands.append(Command(self.rental_services.repository.update, self.rental_services.repository.change_rental_client(rental, old_name)))
            undo = Command(self.do_commands, undo_commands)
            redo_commands = [Command(self.repository.update, (self.repository.change_client(old_client, name)))]
            for rental in old_rental:
                redo_commands.append(Command(self.rental_services.repository.update, self.rental_services.repository.change_rental_client(rental, name)))
            redo = Command(self.do_commands, redo_commands)
            self.repository.update(self.repository.change_client(self.find_by_id(_id), name))
            self.undo_service.register(Operation(undo, redo))
        else:
            undo = Command(self.repository.update, (self.repository.change_client(old_client, old_name)))
            redo = Command(self.repository.update, (self.repository.change_client(old_client, name)))
            self.repository.update(self.repository.change_client(self.find_by_id(_id), name))
            self.undo_service.register(Operation(undo, redo))
        if isinstance(self.repository, TextFileClientRepository):
            self.repository.save_text_file()
        if isinstance(self.repository, BinaryFileClientRepository):
            self.repository.save_binary_file()

    def list_to_screen(self):
        return self.repository.list()

    def find_by_id(self, _id: int):
        return self.repository.data[_id] if _id in self.repository.data.keys() else None

    def generate_clients(self):
        clients = import_20_clients()
        for one_client in clients:
            self.repository.add(self.repository.create_client(one_client.id, one_client.name))

    def find_name(self, client_name):
        clients, empty = [], 0
        for a_client in self.repository.data.values():
            if a_client.name.lower() == client_name.lower() or client_name.lower() in a_client.name.lower():
                clients.append(a_client)
        if len(clients) == empty:
            raise ServicesError("Not found.")
        return clients
