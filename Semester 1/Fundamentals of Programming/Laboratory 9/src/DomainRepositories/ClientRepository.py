from src.Domain.Client import Client
from src.Repositories.MemoryRepository import MemoryRepository


class ClientRepository(MemoryRepository):
    def __init__(self):
        super().__init__()

    @staticmethod
    def create_client(_id, name):
        return Client(_id, name)

    @staticmethod
    def change_client(client: Client, name):
        client.name = name
        return Client(client.id, client.name)
