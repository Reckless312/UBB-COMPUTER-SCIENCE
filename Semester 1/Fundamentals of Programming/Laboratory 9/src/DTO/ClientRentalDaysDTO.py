from src.Domain.Client import Client


class ClientRentalDaysDTO:
    def __init__(self, client: Client, day_count: int):
        self.client = client
        self.days = day_count

    def __str__(self):
        return "Client " + str(self.client) + " has rented for " + str(self.day_count)

    def __repr__(self):
        return str(self)

    def __lt__(self, other):
        return self.day_count <= other.day_count

    @property
    def clients(self):
        return self.client

    @property
    def day_count(self):
        return self.days
