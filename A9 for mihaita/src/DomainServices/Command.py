class Command:
    def __init__(self, function_name, *functions_parameters):
        self.__function_name = function_name
        self.__function_parameters = functions_parameters

    def call(self):
        return self.__function_name(*self.__function_parameters)

    def __call__(self, *args, **kwargs):
        return self.call()


if __name__ == "__main__":
    pass
