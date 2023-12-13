from src.repository.client_repository import ClientRepository


class ClientServices:
    """
    Knows about ClientRepositories and works with it
    """
    def __init__(self):
        self.repository = ClientRepository()
        self.repository.generate_clients()

    def add(self, _id, client_name):
        _id = self.check_id(_id)
        self.repository.add(self.repository.create_client(_id, client_name))

    def remove(self, _id):
        _id = self.check_id(_id)
        self.repository.remove(_id)

    def update(self, _id, client_name):
        _id = self.check_id(_id)
        self.repository.update(self.repository.create_client(_id, client_name))

    def list_to_screen(self):
        return self.repository.list()

    def search_with_id(self, _id):
        _id = self.check_id(_id)
        return self.repository.find_by_id(_id)

    def search_with_name(self, client_name):
        return self.repository.find_name(client_name)

    @staticmethod
    def check_id(_id):
        """
        Checks if the id is a valid one
        :param _id: representation of object
        :return: TypeError / int
        """
        try:
            _id = int(_id)
            return _id
        except ValueError:
            raise TypeError("Not an integer.")


if __name__ == "__main__":
    pass
