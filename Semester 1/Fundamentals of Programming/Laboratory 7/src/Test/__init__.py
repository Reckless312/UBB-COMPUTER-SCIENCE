import unittest
from src.services import Services
"""
Connects to Services to have access to a repository and the "add" function 
"""


class TestMemory(unittest.TestCase):
    def setUp(self):
        self.instruction = Services()

    def test_add_memory_repository(self):
        first_element = 0
        self.assertEqual(len(self.instruction.repository.storage_of_complex_numbers), 0)
        self.instruction.add(2.5, 3)
        self.assertEqual(len(self.instruction.repository.storage_of_complex_numbers), 1)
        number = self.instruction.repository.storage_of_complex_numbers[first_element]
        self.assertEqual(number.get_real_part, 2.5)
        self.assertEqual(number.get_imaginary_part, 3)
        try:
            self.instruction.add("word1", "word2")
        except ValueError as ve:
            self.assertEqual(len(self.instruction.repository.storage_of_complex_numbers), 1)


if __name__ == "__main__":
    unittest.main()
