import unittest


class TestMemory(unittest.TestCase):
    def setUp(self):
        self.memory_repository = MemoryRepository()
        self.text_file_repository = TextFileRepository()
        self.binary_file_repository = BinaryFileRepository()
        self.instructions_memory_repository = Services(self.memory_repository.storage_of_complex_numbers, self.memory_repository.undo_stack)
        self.instructions_text_file_repository = Services(self.text_file_repository.storage_of_complex_numbers, self.text_file_repository.undo_stack)
        self.instructions_binary_file_repository = Services(self.binary_file_repository.storage_of_complex_numbers, self.binary_file_repository.undo_stack)

    def test_add_memory_repository(self):
        first_element = 0
        self.assertEqual(len(self.memory_repository.storage_of_complex_numbers), 0)
        self.instructions_memory_repository.add(ComplexNumber(2.5, 3))
        self.assertEqual(len(self.memory_repository.storage_of_complex_numbers), 1)
        number = self.memory_repository.storage_of_complex_numbers[first_element]
        self.assertEqual(number.get_real_part, 2.5)
        self.assertEqual(number.get_imaginary_part, 3)
        try:
            self.instructions_memory_repository.add(ComplexNumber("word1", "word2"))
        except ValueError as ve:
            self.assertEqual(len(self.memory_repository.storage_of_complex_numbers), 1)

    def test_add_text_file_repository(self):
        first_element = 0
        self.assertEqual(len(self.text_file_repository.storage_of_complex_numbers), 0)
        self.instructions_text_file_repository.add(ComplexNumber(17.25, 0.22))
        self.assertEqual(len(self.text_file_repository.storage_of_complex_numbers), 1)
        number = self.text_file_repository.storage_of_complex_numbers[first_element]
        self.assertEqual(number.get_real_part, 17.25)
        self.assertEqual(number.get_imaginary_part, 0.22)
        try:
            self.instructions_text_file_repository.add(ComplexNumber("food", "water"))
        except ValueError as ve:
            self.assertEqual(len(self.text_file_repository.storage_of_complex_numbers), 1)

    def test_add_binary_file_repository(self):
        first_element = 0
        self.assertEqual(len(self.binary_file_repository.storage_of_complex_numbers), 0)
        self.instructions_binary_file_repository.add(ComplexNumber(2521.2521, 1000.01))
        self.assertEqual(len(self.binary_file_repository.storage_of_complex_numbers), 1)
        number = self.binary_file_repository.storage_of_complex_numbers[first_element]
        self.assertEqual(number.get_real_part, 2521.2521)
        self.assertEqual(number.get_imaginary_part, 1000.01)
        try:
            self.instructions_binary_file_repository.add(ComplexNumber("python", "c++"))
        except ValueError as ve:
            self.assertEqual(len(self.binary_file_repository.storage_of_complex_numbers), 1)


if __name__ == "__main__":
    unittest.main()