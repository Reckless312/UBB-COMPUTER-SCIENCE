from src.DomainRepositories.ClientRepository import ClientRepository


class TextFileClientRepository(ClientRepository):
    def __init__(self, file_name: str = "data.bin"):
        super().__init__()
        self.file = file_name

    def load_text_file(self):
        try:
            file = open(self.file, "r")
            for line in file:
                client = line[:-1].split()
                _id, after_keyword, client_name = 1, 4, ""
                while after_keyword <= len(client) - 1:
                    client_name = client_name + client[after_keyword] + " "
                    after_keyword += 1
                client_name = client_name.split()
                client_name = " ".join(client_name)
                self.add(self.create_client(int(client[_id]), client_name))
            file.close()
        except FileNotFoundError:
            print("NO FILE TO OPEN!")

    def save_text_file(self):
        file = open(self.file, "w")
        for client in self.data.keys():
            file.write("%s\n" % self.data[client])
        file.close()
