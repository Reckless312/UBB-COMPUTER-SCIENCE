from src.domain.client import Client, import_20_clients
from src.repository.memory_repository import MemoryRepository, RepositoryError


class ClientRepository(MemoryRepository):
    """
    Subclass of MemoryRepository, inherits attributes
    """
    def __init__(self):
        super().__init__()

    def find_name(self, client_name):
        """
        Find clients by their name
        :param client_name: str, name to search
        :return: Clients list
        """
        clients, empty = [], 0
        for a_client in self.data.values():
            if a_client.name.lower() == client_name.lower() or client_name.lower() in a_client.name.lower():
                clients.append(a_client)
        if len(clients) == empty:
            raise RepositoryError("Not found.")
        return clients

    def generate_clients(self):
        """
        Generates 20 clients
        :return: changes Clients
        """
        clients = import_20_clients()
        for one_client in clients:
            self.add(one_client)

    @staticmethod
    def create_client(_id, name):
        """
        Creates new client
        :param _id: representation
        :param name: str, name of client
        :return: Client
        """
        return Client(_id, name)
