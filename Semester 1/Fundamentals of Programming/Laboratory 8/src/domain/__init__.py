"""
The Complex Number class is presented here, short since we don't need to change much about them
"""


class ComplexNumber:
    def __init__(self, real_part, imaginary_part):
        """
        Sets up a complex number of form a + b * i
        :param real_part: "a" -> real number
        :param imaginary_part: "b" -> coefficient for the imaginary
        """
        try:
            self.real = float(real_part)
            self.imaginary = float(imaginary_part)
        except ValueError as ve:
            raise ValueError("NOT A NUMBER")

    def __str__(self):
        """
        The representation of a complex number: (a + b * i)
        :return: string
        """
        if self.imaginary > 0:
            return f"{self.real} + {self.imaginary} * i"
        else:
            return f"{self.real} - {abs(self.imaginary)} * i"

    @property
    def get_real_part(self):
        return self.real

    @property
    def get_imaginary_part(self):
        return self.imaginary


if __name__ == "__main__":
    pass
